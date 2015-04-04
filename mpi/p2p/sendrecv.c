/*
 * This can work with any number of processes.
 * This perform ring exchange.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int sendrecv();

int comm_size, myid;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  sendrecv();

  MPI_Finalize();
  return 0;
}

int sendrecv() {
  int dst, src, tag1, tag2;
  int sdata, rdata;
  MPI_Status st;

  sdata = myid;
  dst = (myid + 1 >= comm_size)? 0 : myid + 1;
  src = (myid - 1 < 0)? comm_size - 1 : myid - 1;
  if (myid % 2 == 0) {
    tag1 = 1000;
    tag2 = 1001;
  } else {
    tag1 = 1001;
    tag2 = 1000;
  }

  MPI_Sendrecv(&sdata, 1, MPI_INT, dst, tag1,
	       &rdata, 1, MPI_INT, src, tag2,
	       MPI_COMM_WORLD, &st);

  printf("Rank[%d]: I got a message from Rank[%d]: %d\n",
	 myid, st.MPI_SOURCE, rdata);

  return 0;
}
