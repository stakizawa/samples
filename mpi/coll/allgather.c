/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define PART_SIZE 2

void print_array(int *array, int count, const char *msg);
int allgather();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  allgather();

  MPI_Finalize();
  return 0;
}

int allgather() {
  int array[PART_SIZE];
  int *gathered_array, gathered_count;
  char output_msg[16];
  int i;

  // initialize arrays
  gathered_count = PART_SIZE * size;
  gathered_array = (int*)malloc(gathered_count * sizeof(int));

  for (i = 0; i < PART_SIZE; i++) {
    array[i] = myid + 10 * i;
  }
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(array, PART_SIZE, output_msg);

  // do allgather
  MPI_Allgather(array, PART_SIZE, MPI_INT,
		gathered_array, PART_SIZE, MPI_INT,
		MPI_COMM_WORLD);

  print_array(gathered_array, gathered_count, "Gathered array: ");

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
