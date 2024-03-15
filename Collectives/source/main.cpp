#include <mpi.h>
#include <vector>
#include <iostream>
#include <random>

using std::vector;
// Section 2, Exercise 1 Using Scatter
int main()
{
    MPI_Init(NULL, NULL);

    const int N = 16;

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_proc; // size of the process
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    int *buffer;

    if (rank == 0)
    {
        // buffer size % proc_size == 0

        buffer = new int[N];
        // ONE MORE THING: cannot initiate default value to new int[N] BECAUSE it is in "heap memory" -> the compiler doesn't know the size until runtime

        for (size_t i = 0; i < N; i++)
        {
            buffer[i] = i;
        }

        // int buff_size = N * sizeof(int);
        // int *buff_attach = (int*)malloc(buff_size); // AVOID this, because pointer L38 will move to numbers, and malloc becomes memory leak
        // int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
        // buffer = numbers;
        // MPI_Buffer_attach(buffer, buff_size); // NO NEED TO ATTACH buffer, because this handles different use case like send & receive but there is await
    }

    int buff_other_size = (N / n_proc) * sizeof(int);
    int *buffer_other = new int[N / n_proc];

    // https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node72.html
    MPI_Scatter(buffer, N / n_proc, MPI_INT, buffer_other, N / n_proc, MPI_INT, 0, MPI_COMM_WORLD);

    // print data from receiving, including rank 0
    printf("This is value of receiving buffer (rank %d):", rank);
    for (size_t i = 0; i < (N / n_proc); i++)
    {
        printf(" %d ", buffer_other[i]);
    }
    printf("\n");

    // TODO: deallocate after finalize; but FAILED
    // ANSWER: should check rank == 0 because the allocation is only in rank 0; should not allocate 'buffer' in global because it will waste memory space for other ranks
    if (rank == 0)
    {
        delete[] buffer;
    }
    delete[] buffer_other;

    MPI_Finalize();

    return 0;
}