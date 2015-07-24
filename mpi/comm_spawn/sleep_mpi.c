#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int self, size;
    MPI_Comm parent;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &self);
    MPI_Comm_get_parent(&parent);
    if (parent != MPI_COMM_NULL) {
        MPI_Comm_remote_size(parent, &size);
        if (size != 1) {
            fprintf(stderr, "Parent MPI program is wrong\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
    }

    printf("sleep starts on Rank[%d]\n", self);
    sleep(30);
    printf("sleep ends on Rank[%d]\n", self);

    if (parent != MPI_COMM_NULL) {
        MPI_Barrier(parent);
    }
    MPI_Finalize();
    return 0;
}
