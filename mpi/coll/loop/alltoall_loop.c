/*
 * This program can work with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *each_vector, data_id, send_count;
  int *recv_vector, recv_count;
  //char output_msg[16];
  int i, c;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // print size by root
  //if (myid == 0) {
  //  printf("Process Count: %d\n", size);
  //}

  for (c = 0; c < 10; c++) {
    send_count = size * (c+1);
    recv_count = size * (c+1);

    // init vector on each process
    each_vector = (int*)malloc(send_count * sizeof(int));
    data_id = myid * 1000;
    for (i = 0; i < send_count; i++) {
      each_vector[i] = data_id + i;
    }
    // print vector
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(each_vector, send_count, output_msg);

    // init recv vector
    recv_vector = (int*)malloc(recv_count * sizeof(int));
    for (i = 0; i < recv_count; i++) {
      recv_vector[i] = -1;
    }

    // do alltoall
    MPI_Alltoall(each_vector, c+1, MPI_INT,
		 recv_vector, c+1, MPI_INT, MPI_COMM_WORLD);

    //print_array(recv_vector, recv_count, output_msg);

    free(each_vector);
    free(recv_vector);
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
