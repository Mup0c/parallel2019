#include <mpi.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    float message;
    int n, i, rank;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    float rankf = rank;
    rankf += 0.001;
    if (rank == 4) {
        std::cout << "Hello from main process " << rank << "\n";
        for (i=1; i<n; i++){
            MPI_Recv(&message, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            std::cout << "Hello from process " << message << std::endl;
        }
    } else {
        MPI_Send(&rankf,1,MPI_FLOAT,4,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}