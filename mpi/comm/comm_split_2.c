#include <stdio.h>
#include <mpi.h>

#define NPROCS_SUB 2

void split_comm(MPI_Comm old_comm, int old_comm_rank, MPI_Comm *new_comm);
int task(MPI_Comm comm, int parent_rank);

int
main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int comm_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (comm_size < NPROCS_SUB) {
        if (rank == 0) {
            fprintf(stderr, "Specify at least %d processes\n", NPROCS_SUB);
        }
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Comm new_comm;
    split_comm(MPI_COMM_WORLD, rank, &new_comm);
    task(new_comm, rank);

    MPI_Finalize();
    return 0;
}


void
split_comm(MPI_Comm old_comm, int old_comm_rank, MPI_Comm *new_comm)
{
    int color = old_comm_rank / NPROCS_SUB;
    MPI_Comm_split(old_comm, color, old_comm_rank, new_comm);
}

int
task(MPI_Comm comm, int parent_rank)
{
    int comm_size, rank;
    MPI_Comm_size(comm, &comm_size);
    MPI_Comm_rank(comm, &rank);

    int val;
    if (rank == 0) {
        val = 10;
        MPI_Send(&val, 1, MPI_INT, 1, 1000, comm);
        printf("[%d(%d)] sent a message.\n", parent_rank, rank);
    } else {
        MPI_Status stat;
        MPI_Recv(&val, 1, MPI_INT, 0, 1000, comm, &stat);
        if (val != 10) {
            fprintf(stderr, "[%d(%d)] Send/Recv failed.\n", parent_rank, rank);
            return 0;
        }
        printf("[%d(%d)] received a message.\n", parent_rank, rank);
    }

    return 1;
}

