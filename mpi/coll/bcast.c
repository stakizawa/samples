/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int bcast_barrier();

int myid;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  bcast_barrier();

  MPI_Finalize();
  return 0;
}

int bcast_barrier() {
  int data;

  MPI_Barrier(MPI_COMM_WORLD);
 
  if (myid == 0) {
    data = 100;
  }
  MPI_Bcast(&data, 1 , MPI_INT, 0, MPI_COMM_WORLD);
  if (myid != 0) {
    printf("Rank[%d]: %d\n", myid, data);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  return 0;
}
