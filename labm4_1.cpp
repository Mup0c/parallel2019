#include <mpi.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    double time_start, time_finish;
    time_start = MPI_Wtime();
    int message;
    int n, i, rank;
    int anscount = 0;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        for (i=1; i<n; i++){
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (message % 7 == 0 and (message * 2) % 7 == 0) {
                anscount++;
            }
        }
    } else {
        MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    if (rank == 0) {
        if (anscount >= 2){
            std::cout << "Да. Содержит чисел, кратных 3.5 и 7: " << anscount << std::endl;
        } else {
            std::cout << "Нет. Содержит чисел, кратных 3.5 и 7: " << anscount << std::endl;
        }
    }
    time_finish = MPI_Wtime();
    cout << "Process " << rank << " time = " << (time_finish - time_start) << endl;
    return 0;
}