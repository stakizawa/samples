/*
 * This works with any number of processes.
 * Even numbered process sends a message to add (id+1) numbered process.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int send_recv_any();

int comm_size, myid;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  send_recv_any();

  MPI_Finalize();
  return 0;
}

int send_recv_any() {
  int data1, data2;

  if (myid % 2 == 0) {
    int dest = myid + 1;
    if (dest < comm_size) {
      data1 = (myid + 1) * 100;
      data2 = (myid + 1) * 100 + 1;
      MPI_Send(&data1, 1, MPI_INT, dest, 1000, MPI_COMM_WORLD);
      MPI_Send(&data2, 1, MPI_INT, dest, 1001, MPI_COMM_WORLD);
    }
  } else {
    MPI_Status st1, st2;
    MPI_Recv(&data1, 1, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &st1);
    MPI_Recv(&data2, 1, MPI_INT, MPI_ANY_SOURCE, 1001, MPI_COMM_WORLD, &st2);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n",
	   myid, st1.MPI_SOURCE, data1);
    printf("Rank[%d]: I got a message from Rank[%d]: %d\n",
	   myid, st2.MPI_SOURCE, data2);
  }

  return 0;
}
