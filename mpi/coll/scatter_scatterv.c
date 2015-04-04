#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define ARRAY_SIZE 8

void print_array(int *array, int count, const char *msg);
int scatter_scatterv();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  scatter_scatterv();

  MPI_Finalize();
  return 0;
}

int scatter_scatterv() {
  int array[ARRAY_SIZE];
  int *send_counts;
  int *recv_array, recv_count, remainder, *displs;
  char output_msg[16];
  int i;

  // initialize array on rank 0
  if (myid == 0) {
    for (i = 0; i < ARRAY_SIZE; i++) {
      array[i] = i+1;
    }
    print_array(array, ARRAY_SIZE, "Original Array: ");
  }

  recv_count = ARRAY_SIZE / size;
  remainder = ARRAY_SIZE % size;

  if (remainder != 0) {
    // do scatterv
    if (myid == 0) {
      send_counts = (int *)malloc(size * sizeof(int));
      displs = (int *)malloc(size * sizeof(int));
      for (i = 0; i < size; i++) {
	send_counts[i] = recv_count;
	if (i < remainder)
	  send_counts[i]++;
	if (i == 0)
	  displs[i] = 0;
	else
	  displs[i] = displs[i-1] + send_counts[i-1];
      }
      recv_count++;
    } else {
      send_counts = (void*)0;
      displs = (void*)0;
      if (myid < remainder) recv_count++;
    }

    recv_array = (int *)malloc(recv_count * sizeof(int));
    MPI_Scatterv(array, send_counts, displs, MPI_INT,
		 recv_array, recv_count, MPI_INT,
		 0, MPI_COMM_WORLD);
  } else {
    // do scatter
    recv_array = (int *)malloc(recv_count + sizeof(int));
    MPI_Scatter(array, recv_count, MPI_INT,
		recv_array, recv_count, MPI_INT,
		0, MPI_COMM_WORLD);
  }

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
