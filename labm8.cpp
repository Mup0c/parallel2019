#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

void sum_cascade(int rank, int processes, const vector<int>& v) {
    auto leftChild  = 2*rank + 1;
    auto rightChild = 2*rank + 2;

    if (rank == 0) {
        auto vecPointer = v.data();
        auto leftSize = v.size() / 2;
        auto rightSize = v.size() - leftSize;

        auto start_time = MPI_Wtime();

        MPI_Send(vecPointer, leftSize, MPI_INT, leftChild, 0, MPI_COMM_WORLD);
        MPI_Send(vecPointer + leftSize, rightSize, MPI_INT, rightChild, 0, MPI_COMM_WORLD);

        int sumL, sumR;
        MPI_Recv(&sumL, 1, MPI_INT, leftChild,  MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&sumR, 1, MPI_INT, rightChild, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int res = sumL + sumR;
        cout << "CASCADE - time: " << MPI_Wtime() - start_time << "| size: " << v.size() << "| result: " << res << endl;
    }
    else {
        MPI_Status status;
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        int count;
        MPI_Get_count(&status, MPI_INT, &count);
        auto arr = new int[count];

        MPI_Recv(arr, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        auto leftSize = count / 2;
        auto rightSize = count - leftSize;

        auto hasLeftChild = leftChild < processes;
        auto hasRightChild = rightChild < processes;

        int sumL = 0, sumR = 0;

        if (hasLeftChild) {
            MPI_Send(arr, leftSize, MPI_INT, leftChild, 0, MPI_COMM_WORLD);
            MPI_Recv(&sumL, 1, MPI_INT, leftChild,  MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else {
            for (int i = 0; i < leftSize; i++) {
                sumL += arr[i];
            }
        }

        if (hasRightChild) {
            MPI_Send(arr+ leftSize, rightSize, MPI_INT, rightChild, 0, MPI_COMM_WORLD);
            MPI_Recv(&sumR, 1, MPI_INT, rightChild, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        else {
            for (int i = leftSize; i < count; i++) {
                sumR += arr[i];
            }
        }

        auto sum = sumL + sumR;

        MPI_Send(&sum, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);

        delete[] arr;
    }
}

void sum_reduce(int rank, int processes, const vector<int>& v) {
    int size, res, sum = 0;
    if (rank == processes - 1) {
        size = v.size() - (processes - 1) * (v.size() / processes);
    } else {
        size = v.size() / processes;
    }

    for (int i = 0; i < size; i++) {
        sum += v[rank * (v.size() / processes) + i];
    }

    double start_time = MPI_Wtime();
    MPI_Reduce(&sum, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        cout << "REDUCE - time: " << MPI_Wtime() - start_time << "| size: " << v.size() << "| result: " << res << endl;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, processes;
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vector_size = 100000000;
    vector<int> v_casc(vector_size/processes, 1);
    vector<int> v(vector_size, 1);

    sum_reduce(rank, processes, v);
    sum_cascade(rank, processes, v_casc);


    MPI_Finalize();
}