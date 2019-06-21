#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

void dot_production(const std::vector<int>& vector_a, const std::vector<int>& vector_b, int rank, int processors)
{
    int vec_size = vector_a.size();
    int chunk_size = vector_a.size() / processors;
    int last_chunk_size = vec_size - (processors - 1)*chunk_size;

    int start_index = rank * chunk_size;
    int after_last_index = start_index + chunk_size;
    int local_sum = 0;

    if (rank != processors - 1) {
        for (int i = start_index; i < after_last_index; i++) {
            local_sum += vector_a[i] * vector_b[i];
        }
    }
    else {
        for (int i = start_index; i < start_index + last_chunk_size; i++) {
            local_sum += vector_a[i] * vector_b[i];
        }
    }

    int result = 0;
    MPI_Reduce(&local_sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        cout << result << endl;

}


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vector_size = 40000000;

    std::vector<int> vector_a(vector_size, 1);
    std::vector<int> vector_b(vector_size, 1);
    while (vector_size > 10){
        vector_a.resize(vector_size);
        vector_b.resize(vector_size);
        double start_time;
        if (rank == 0) {
            start_time = MPI_Wtime();
        }

        dot_production(vector_a, vector_b, rank, size);
        if (rank == 0) {
            cout << "Time " << MPI_Wtime() - start_time << endl;
        }
        vector_size /= 10;
    }


    MPI_Finalize();
}