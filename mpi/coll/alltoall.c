/*
 * This program can work with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);
int alltoall();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  alltoall();

  MPI_Finalize();
  return 0;
}

int alltoall() {
  int *each_vector, data_id, send_count;
  int *recv_vector, recv_count;
  char output_msg[16];
  int i;

  send_count = size;
  recv_count = size;

  // print size by root
  if (myid == 0) {
    printf("Process Count: %d\n", size);
  }

  // init vector on each process
  each_vector = (int*)malloc(send_count * sizeof(int));
  data_id = myid * 10;
  for (i = 0; i < send_count; i++) {
    each_vector[i] = data_id + i;
  }
  // print vector
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(each_vector, send_count, output_msg);

  // init recv vector
  recv_vector = (int*)malloc(recv_count * sizeof(int));
  for (i = 0; i < recv_count; i++) {
    recv_vector[i] = -1;
  }

  // do alltoall
  MPI_Alltoall(each_vector, 1, MPI_INT,
	       recv_vector, 1, MPI_INT, MPI_COMM_WORLD);

  print_array(recv_vector, recv_count, output_msg);

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
