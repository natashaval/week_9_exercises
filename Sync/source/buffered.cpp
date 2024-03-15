#include <mpi.h>

int main()
{
    MPI_Init(NULL, NULL);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n_ranks;
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
    
    int neighbour_rank;
    MPI_Request R;

    // to answer syncronized.cpp deadlock

// https://www.mpi-forum.org/docs/mpi-1.1/mpi-11-html/node42.html
// https://rookiehpc.org/mpi/docs/mpi_bsend/index.html
    int buff_size = MPI_BSEND_OVERHEAD + sizeof(int);
    int *buff_attach = (int*)malloc(buff_size);
    MPI_Buffer_attach(buff_attach, buff_size);

    MPI_Bsend(&rank, 1, MPI_INT, (rank+1)%n_ranks, 0, MPI_COMM_WORLD);

    MPI_Recv(&neighbour_rank, 1, MPI_INT, (rank-1)%n_ranks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("My rank is %d and the neighbour is rank %d\n", rank, neighbour_rank);

    MPI_Buffer_detach(&buff_attach, &buff_size);
    free(buff_attach);

    MPI_Finalize();

    return 0;
}