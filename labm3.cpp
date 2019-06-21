#include <mpi.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int message;
    int n, i, rank;
    int anscount = 0;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (i=1; i<n; i++){
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            message += n;
            if (message % 7 == 0 || message % 5 == 0 || message % 3 == 0) {
                std::cout << message << std::endl;
                anscount++;
            }
        }
    } else {
        MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    if (rank == 0) {
        if (anscount >= 2){
            std::cout << "Да. Содержит чисел, кратных 3 5 и 7: " << anscount << std::endl;
        } else {
            std::cout << "Нет. Содержит чисел, кратных 3.5 и 7: " << anscount << std::endl;
        }
    }
    return 0;
}