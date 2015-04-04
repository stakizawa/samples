/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *array, *result;
  //char output_msg[16];
  int i, j;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (j = 1; j <= 10; j++) {
    // initialize arrays
    array = (int*)calloc(j, sizeof(int));
    if (myid == 0) {
      result = (int*)calloc(j, sizeof(int));
    } else {
      result = NULL;
    }
    for (i = 0; i < j; i++) {
      array[i] = myid * j + i + 1;
    }
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(array, j, output_msg);

    // do reduce
    MPI_Reduce(array, result, j, MPI_INT,
	       MPI_SUM, 0, MPI_COMM_WORLD);

    // print reduced array on root
    //if (myid == 0) {
    //  print_array(result, j, "Reduced array: ");
    //}
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
