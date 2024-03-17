#include <mpi.h>
#include <random> 

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int process_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);

    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    if (process_id == 0)
    {
        const int N = 256;
        std::mt19937_64 rng;
        std::uniform_real_distribution<double> dist(0, 1);
        double master_list[N];
        for(int i = 0; i < N; i++)
        {
            master_list[i] = dist(rng);
        }

        int listSize = N / num_proc; // We are using a multiple of four to avoid dealing with remainders!

        // Send the list data in messages
        for(int i = 1; i < num_proc; i++)
        {
            double * buffer_start = master_list + listSize*i;
            MPI_Send(buffer_start,
                     listSize,
                     MPI_DOUBLE,
                     i,
                     0,
                     MPI_COMM_WORLD);
        }
    }

    printf("Hello World! Kind regards, Process %d of %d\n", process_id, num_proc);

    MPI_Finalize();
}