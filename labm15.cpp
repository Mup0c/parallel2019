#include "mpi.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

void print(float *a, char *b, size_t size, int rank, bool before = false) {
    string out;
    if (before)
        out += "BEFORE CAST: \n";
    out += "rank: " + to_string(rank) + "\na: ";
    for (auto i = 0; i < size; i++)
        out += to_string(a[i]) + " ";
    out += "\nb: ";

    for (auto i = 0; i < size; i++)
        out += string(1, b[i]) + " ";
    out += "\n\n";
    cout << out;
}

int main(int argc, char **argv) {
    int size, rank, position, i;
    float a[10];
    char b[10], buf[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(i = 0; i<10; i++){
        a[i] = rank + 1.0;

        if(rank == 0)
            b[i]='a';
        else
            b[i] = 'b';
    }

    position = 0;
    print(a, b, 10, rank, true);
    if(rank == 0){
        print(a, b, 10, rank);

        MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
        MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);
        MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
    } else {
        MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
        position = 0;
        MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
        print(a, b, 10, rank);
    }

    MPI_Finalize();
}