#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;



int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vector_size = 100000000;

    vector<int>vec(vector_size, 1);

    vecSum(rank, size, vec);

    MPI_Finalize();
}