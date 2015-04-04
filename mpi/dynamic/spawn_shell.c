#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

static char *worker_mpi = "./spawn_child";
static char *worker = "./sleep.sh";
static char *worker_wrapper = "./mpi_wrap.sh";

int main(int argc, char **argv) {
    int world_size, *universe_size, flag;
    MPI_Comm everyone;
    char *cmd_args[2] = { worker, NULL};

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE,
                      &universe_size, &flag);
    if (!flag) {
        fprintf(stderr, "Failt to get universe size\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 0;
    }
    if (*universe_size == 1) {
        fprintf(stderr, "No room to start workers\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
        return 0;
    }
    printf("Universe size: %d\n", *universe_size);

#ifdef SHELL_ASIS
    // In case of executing commands as it is
    // !!WARNING!!   Main MPI program never stops
    MPI_Comm_spawn(worker, MPI_ARGV_NULL, 2,
                   MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,
                   MPI_ERRCODES_IGNORE);
#elif MPI_WRAP
    MPI_Comm_spawn(worker_wrapper, MPI_ARGV_NULL, 2,
                   MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,
                   MPI_ERRCODES_IGNORE);
    MPI_Barrier(everyone);
#else
    // In case of executing commands as MPI processes
    MPI_Comm_spawn(worker_mpi, cmd_args, 2,
                   MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone,
                   MPI_ERRCODES_IGNORE);
    MPI_Barrier(everyone);
#endif

    printf("MPI_Comm_spawn is called\n");

    MPI_Finalize();
    return 0;
}
