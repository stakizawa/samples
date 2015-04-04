/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *array, data_count;
  int *recv_array;
  //char output_msg[16];
  int count, i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (count = 1; count <= 10; count++) {
    // initialize receive array
    recv_array = (int *)malloc(count * sizeof(int));

    // initialize array on rank 0
    if (myid == 0) {
      data_count = count * size;
      array = (int*)malloc(data_count * sizeof(int));
      for (i = 0; i < data_count; i++) {
	array[i] = i+1;
      }
      //print_array(array, data_count, "Original Array: ");
    } else {
      data_count = -1;
      array = (void*)0;
    }

    // do scatter
    MPI_Scatter(array, count, MPI_INT,
		recv_array, count, MPI_INT,
		0, MPI_COMM_WORLD);

    // print scattered array on each proc
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(recv_array, count, output_msg);

    free(array);
    free(recv_array);
  }

  MPI_Finalize();
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
