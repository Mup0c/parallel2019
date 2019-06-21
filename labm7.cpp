#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

void sendrecv(int length, int rank) {
    auto message = new char[length];
    int N = 10;
    double elapsed_time = 0;

    for (int i = 0; i < N; i++) {
        if (rank == 0) {
            double start_time = MPI_Wtime();
            MPI_Send(message, length, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(message, length, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            elapsed_time += (MPI_Wtime() - start_time);
        } else if (rank == 1) {
            MPI_Recv(message, length, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(message, length, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        auto sizeInKB = length / 1024;
        cout << "__________" << endl;
        cout << "Size (KB): " << sizeInKB << " time (s): " << elapsed_time/N << endl;
        cout << "bandwidth (KB/s): " << 2*N*(sizeInKB/elapsed_time) << endl;
    }

    delete[] message;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    vector<int> sizes = {100000, 40000, 20000, 10000, 5000, 2000, 1000, 500, 100};
    for (const auto s : sizes) {
        sendrecv(1024*s, rank);
    }
    MPI_Finalize();
}