#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <sstream>

void client(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& input, const std::vector<std::string>& task);
void server(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& input);

int main(int argc, char* argv[]) {

    std::string input;
    std::vector<std::string> task = {
            "5+3",
            "res/2",
            "24/res",
            "res*res",
            "res-6",
            "res-2",
            "res-2",
            ""
    };

    omp_lock_t read_lock, write_lock;

    omp_init_lock(&read_lock);
    omp_set_lock(&read_lock);

    omp_init_lock(&write_lock);

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                server(read_lock, write_lock, input);
            }
#pragma omp section
            {
                client(read_lock, write_lock, input, task);
            }
        }
    }
    return 0;
}

void client(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& input, const std::vector<std::string>& task) {
    for (const auto& command : task) {
        omp_set_lock(&write_lock);
        input = command;
        omp_unset_lock(&read_lock);
    }
}

void server(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& input) {
    int res = 0;
    int term1, term2;
    char op;

    while (true) {
        omp_set_lock(&read_lock);
        std::stringstream ss;
        ss << input;

        if (input.length() == 0) {
            std::cout << res << std::endl;
            return;
        }

        if (ss.peek() == 'r') {
            term1 = res;
            ss.get(); ss.get(); ss.get();
            ss >> op;
            if (input[4] == 'r') {
                term2 = res;
            } else {
                ss >> term2;
            }
        } else {
            ss >> term1;
            ss >> op;
            if (ss.peek() == 'r') {
                term2 = res;
            }
            else {
                ss >> term2;
            }
        }

        if (op == '+')
            res = term1 + term2;
        else if (op == '-')
            res = term1 - term2;
        else if (op == '/')
            res = term1 / term2;
        else if (op == '*')
            res = term1 * term2;

        omp_unset_lock(&write_lock);
    }
}