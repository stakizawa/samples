/*
 * This program can work with any number of processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *send_vector, sv_size, *send_counts, *sdispls;
  int *recv_vector, rv_size, *recv_counts, *rdispls;
  //char output_msg[16];
  int count, i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // print size by root
  //if (myid == 0) {
  //  printf("Process Count: %d\n", size);
  //}

  for (count = 1; count <= 10; count++) {
    // init send vector
    sv_size = size * (myid + 1) * count;
    send_vector = (int*)malloc(sv_size * sizeof(int));
    for (i = 0; i < sv_size; i++) {
      send_vector[i] = 1000 + myid;
    }
    // print vector
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(send_vector, sv_size, output_msg);

    // init send_counts and sdispls
    send_counts = (int*)malloc(size * sizeof(int));
    sdispls     = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
      send_counts[i] = (myid + 1) * count;
      if (i == 0)
	sdispls[i] = 0;
      else
	sdispls[i] = sdispls[i-1] + send_counts[i-1];
    }

    // init recv vector
    rv_size = size * (size + 1) / 2 * count;
    recv_vector = (int*)malloc(rv_size * sizeof(int));
    for (i = 0; i < rv_size; i++) {
      recv_vector[i] = -1;
    }

    // init recv_counts and rdispls
    recv_counts = (int*)malloc(size * sizeof(int));
    rdispls     = (int*)malloc(size * sizeof(int));
    for (i = 0; i < size; i++) {
      recv_counts[i] = (i + 1) * count;
      if (i == 0)
	rdispls[i] = 0;
      else
	rdispls[i] = rdispls[i-1] + recv_counts[i-1];
    }

    // do alltoall
    MPI_Alltoallv(send_vector, send_counts, sdispls, MPI_INT,
		  recv_vector, recv_counts, rdispls, MPI_INT, MPI_COMM_WORLD);

    //print_array(recv_vector, rv_size, output_msg);
    free(send_vector);
    free(send_counts);
    free(sdispls);
    free(recv_vector);
    free(recv_counts);
    free(rdispls);
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
