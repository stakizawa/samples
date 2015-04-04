/*
 * This works with any number of processes.
 * Even numbered process sends a message to add (id+1) numbered process.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int isend_irecv_waitall();

int comm_size, myid;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  isend_irecv_waitall();

  MPI_Finalize();
  return 0;
}

int isend_irecv_waitall() {
  int data1, data2;
  MPI_Request reqs[2];
  MPI_Status stats[2];

  if (myid % 2 == 0) {
    int dest = myid + 1;
    if (dest < comm_size) {
      data1 = (myid + 1) * 100;
      data2 = (myid + 1) * 100 + 1;
      MPI_Isend(&data1, 1, MPI_INT, dest, 1000, MPI_COMM_WORLD, &reqs[0]);
      MPI_Isend(&data2, 1, MPI_INT, dest, 1000, MPI_COMM_WORLD, &reqs[1]);
      MPI_Waitall(2, reqs, stats);
    }
  } else {
    int src = myid - 1;
    MPI_Irecv(&data1, 1, MPI_INT, src, 1000, MPI_COMM_WORLD, &reqs[0]);
    MPI_Irecv(&data2, 1, MPI_INT, src, 1000, MPI_COMM_WORLD, &reqs[1]);
    MPI_Waitall(2, reqs, stats);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n", myid, src, data1);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n", myid, src, data2);
  }

  return 0;
}
