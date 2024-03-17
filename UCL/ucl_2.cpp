#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int process_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    printf("Hello World! Kind regards, Process %d of %d\n", process_id, num_proc);

    MPI_Finalize();
}