/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define COUNT 2

void print_array(int *array, int count, const char *msg);
int allreduce();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  allreduce();

  MPI_Finalize();
  return 0;
}

int allreduce() {
  int array[COUNT], result[COUNT];
  char output_msg[16];
  int i;

  // initialize array
  for (i = 0; i < COUNT; i++) {
    array[i] = myid * COUNT + i + 1;
  }
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(array, COUNT, output_msg);

  // do allreduce
  MPI_Allreduce(array, result, COUNT, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  // print reduced array
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(result, COUNT, "Reduced array: ");

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
