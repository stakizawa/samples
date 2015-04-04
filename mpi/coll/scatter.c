/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);
int scatter();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  scatter();

  MPI_Finalize();
  return 0;
}

int scatter() {
  int *array, data_count;
  int *recv_array, recv_count;
  char output_msg[16];
  int i;

  // initialize receive array
  recv_count = 2;
  recv_array = (int *)malloc(recv_count * sizeof(int));

  // initialize array on rank 0
  if (myid == 0) {
    data_count = recv_count * size;
    array = (int*)malloc(data_count * sizeof(int));
    for (i = 0; i < data_count; i++) {
      array[i] = i+1;
    }
    print_array(array, data_count, "Original Array: ");
  } else {
    data_count = -1;
    array = (void*)0;
  }

  // do scatter
  MPI_Scatter(array, recv_count, MPI_INT,
	      recv_array, recv_count, MPI_INT,
	      0, MPI_COMM_WORLD);

  // print scattered array on each proc
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(recv_array, recv_count, output_msg);

  return 0;
}

void print_array(int *array, int count, const char *msg) {
  int i;
  printf("%s", msg);
  for (i = 0; i < count; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}
