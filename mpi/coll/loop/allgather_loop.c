/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define PART_SIZE 2

#define N 10

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int array[PART_SIZE];
  int *gathered_array, gathered_count;
  //char output_msg[16];
  int i, j;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  for (j = 1; j <= N; j++) {
    // initialize arrays
    gathered_count = PART_SIZE * size;
    gathered_array = (int*)malloc(gathered_count * sizeof(int));

    for (i = 0; i < PART_SIZE; i++) {
      array[i] = myid + 10 * i + j;
    }
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(array, PART_SIZE, output_msg);

    // do allgather
    MPI_Allgather(array, PART_SIZE, MPI_INT,
		  gathered_array, PART_SIZE, MPI_INT,
		  MPI_COMM_WORLD);

    //print_array(gathered_array, gathered_count, "Gathered array: ");

    free(gathered_array);
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
