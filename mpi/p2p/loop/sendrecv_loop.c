/*
 * This can work with any number of processes.
 * This perform ring exchange.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  int comm_size, myid;
  int dst, src, tag1, tag2;
  int *sdata, *rdata;
  MPI_Status st;
  int i, j;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  dst = (myid + 1 >= comm_size)? 0 : myid + 1;
  src = (myid - 1 < 0)? comm_size - 1 : myid - 1;
  if (myid % 2 == 0) {
    tag1 = 1000;
    tag2 = 1001;
  } else {
    tag1 = 1001;
    tag2 = 1000;
  }

  for (i = 1; i <= 10; i++) {
    sdata = (int*)calloc(i, sizeof(int));
    for (j = 0; j < i; j++) sdata[j] = myid;
    rdata = (int*)calloc(i, sizeof(int));

    MPI_Sendrecv(sdata, i, MPI_INT, dst, tag1,
		 rdata, i, MPI_INT, src, tag2,
		 MPI_COMM_WORLD, &st);

/*     printf("Rank[%d]: I got %d messages from Rank[%d]\n", */
/* 	   myid, i, st.MPI_SOURCE); */
    free(sdata);
    free(rdata);
  }

  MPI_Finalize();
  return 0;
}
