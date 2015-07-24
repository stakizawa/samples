#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int size, self;
    MPI_Comm parent;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &self);
    if (argc != 2) {
        if (self == 0) {
            fprintf(stderr, "specify a command\n");
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }
    MPI_Comm_get_parent(&parent);
    if (parent == MPI_COMM_NULL) {
        fprintf(stderr, "No parent MPI program\n");
    } else {
        MPI_Comm_remote_size(parent, &size);
        if (size != 1) {
            fprintf(stderr, "Parent MPI program is wrong\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 1;
    }

    if (pid > 0) { // parent
        int status;
        pid_t r = waitpid(pid, &status, 0);
        if (r < 0) {
            fprintf(stderr, "fail on waitpid");
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child process failed on Rank[%d]\n", self);
        }
    }

    if (pid == 0) { // child
        execv(argv[1], 0);
    }

    if (parent != MPI_COMM_NULL) {
        MPI_Barrier(parent);
    }

    MPI_Finalize();
    return 0;
}
