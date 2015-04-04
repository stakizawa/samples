#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int rank, comm_size, universe_size, *universe_sizep, flag;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE,
		    &universe_sizep, &flag);
  if (!flag) {
    printf("This MPI does not support UNIVERSE_SIZE.\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  universe_size = *universe_sizep;

  if (rank == 0) {
    printf("Universe Size: %d\n", universe_size);
    printf("Static size  : %d\n", comm_size);
  }
  MPI_Finalize();
  return 0;
}
