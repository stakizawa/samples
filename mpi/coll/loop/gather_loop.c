/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *array;
  int *gathered_array, gathered_count;
  //char output_msg[16];
  int count, i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (count = 1; count <= 10; count++) {
    // initialize arrays
    if (myid == 0) {
      gathered_count = count * size;
      gathered_array = (int*)malloc(gathered_count * sizeof(int));
    } else {
      gathered_count = -1;
      gathered_array = (void*)0;
    }
    array = (int*)malloc(count * sizeof(int));
    for (i = 0; i < count; i++) {
      array[i] = myid + 10 * i;
    }
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(array, count, output_msg);

    // do gather
    MPI_Gather(array, count, MPI_INT,
	       gathered_array, count, MPI_INT,
	       0, MPI_COMM_WORLD);

    // print gathered array on root
    //if (myid == 0) {
    //  print_array(gathered_array, gathered_count, "Gathered array: ");
    //}

    free(gathered_array);
    free(array);
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
