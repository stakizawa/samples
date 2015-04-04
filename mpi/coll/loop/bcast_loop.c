/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_data(int *, int, int);

int main(int argc, char *argv[]) {
  int myid, count, *data;
  int i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  MPI_Barrier(MPI_COMM_WORLD);
 
  for (count = 0; count < 10; count++) {
    data = (int *)malloc((count+1) * sizeof(int));
    if (myid == 0) {
      for (i = 0; i < count+1; i++)
	data[i] = count;
    }

    MPI_Bcast(data, count+1 , MPI_INT, 0, MPI_COMM_WORLD);

    //if (myid != 0)
    //  print_data(data, count+1, myid);

    free(data);

    MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}

void print_data(int *data, int len, int rank) {
  int i;
  printf("Rank[%d]: ", rank);
  for (i = 0; i < len; i++)
    printf("%d ", data[i]);
  printf("\n");
}
