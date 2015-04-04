#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  int myid;
  int n_procs;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

  if (n_procs < 2) {
    if (myid == 0) {
      fprintf(stderr, "n_procs must be bigger than 2\n");
    }
    MPI_Finalize();
    return -1;
  }

  int data = 0;
  MPI_Status status;

  if (myid == 0) {
    data = 100;
    MPI_Send(&data, 1, MPI_INT, 1, 1000, MPI_COMM_WORLD);
  } else if (myid == 1) {
    MPI_Recv(&data, 1, MPI_INT, 0, 1000, MPI_COMM_WORLD, &status);
  }

  printf("Rank[%d]: data=%d\n", myid, data);
  MPI_Finalize();
  return 0;
}
