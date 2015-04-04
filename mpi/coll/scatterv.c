/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);
int scatterv();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  scatterv();

  MPI_Finalize();
  return 0;
}

int scatterv() {
  int *array, data_count;
  int *send_counts;
  int *recv_array, recv_count, *displs;
  char output_msg[16];
  int i;

  // initialize array on rank 0
  if (myid == 0) {
    data_count = size * (size + 1) / 2;
    array = (int*)malloc(data_count * sizeof(int));
    for (i = 0; i < data_count; i++) {
      array[i] = i;
    }
    print_array(array, data_count, "Original Array: ");
  } else {
    data_count = -1;
    array = (void*)0;
  }

  // initialize data for sending
  if (myid == 0) {
    send_counts = (int*)malloc(size * sizeof(int));
    displs = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
      send_counts[i] = i + 1;
      if (i == 0)
	displs[i] = 0;
      else
	displs[i] = displs[i-1] + send_counts[i-1];
    }
  } else {
    send_counts = (void*)0;
    displs = (void*)0;
  }

  recv_count = myid + 1;
  recv_array = (int*)malloc(recv_count * sizeof(int));
  
  MPI_Scatterv(array, send_counts, displs, MPI_INT,
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
