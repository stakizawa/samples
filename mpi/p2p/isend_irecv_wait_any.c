/*
 * This works with any number of processes.
 * Even numbered process sends a message to add (id+1) numbered process.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int isend_irecv_wait_any();

int comm_size, myid;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  isend_irecv_wait_any();

  MPI_Finalize();
  return 0;
}

int isend_irecv_wait_any() {
  int data1, data2;
  MPI_Request r1, r2;
  MPI_Status st1, st2;

  if (myid % 2 == 0) {
    int dest = myid + 1;
    if (dest < comm_size) {
      data1 = (myid + 1) * 100;
      data2 = (myid + 1) * 100 + 1;
      MPI_Isend(&data1, 1, MPI_INT, dest, 1000, MPI_COMM_WORLD, &r1);
      MPI_Isend(&data2, 1, MPI_INT, dest, 1000, MPI_COMM_WORLD, &r2);
      MPI_Wait(&r1, &st1);
      MPI_Wait(&r2, &st2);
    }
  } else {
    MPI_Irecv(&data1, 1, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &r1);
    MPI_Irecv(&data2, 1, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &r2);
    MPI_Wait(&r1, &st1);
    MPI_Wait(&r2, &st2);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n",
	   myid, st1.MPI_SOURCE, data1);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n",
	   myid, st1.MPI_SOURCE, data2);
  }

  return 0;
}
