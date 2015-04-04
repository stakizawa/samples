/*
 * This works with any number of processes.
 * process sends message whose size is "rank + 1"
 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N 10

void print_array(int *array, int count, const char *msg);

int main(int argc, char *argv[]) {
  int myid, size;
  int *array;
  int send_count;
  int *recv_counts, *displs;
  int *gathered_array, gathered_count;
  //char output_msg[16];
  int i, j;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  for (j = 1; j <= N; j++) {
    // initialize arrays on each process
    send_count = myid + 1;
    array = (int*)malloc(send_count * sizeof(int));
    for (i = 0; i < send_count; i++) {
      array[i] = 100 * j + myid;
    }
    //snprintf(output_msg, 16, "Rank[%d]: ", myid);
    //print_array(array, send_count, output_msg);

    // initialize gathered_array on each process
    recv_counts = (int*)malloc(size * sizeof(int));
    displs = (int*)malloc(size * sizeof(int));
    gathered_count = 0;
    for (i = 0; i < size; i++) {
      recv_counts[i] = i + 1;
      if (i == 0)
	displs[i] = 0;
      else
	displs[i] = displs[i-1] + recv_counts[i-1];
      gathered_count += recv_counts[i];
    }
    gathered_array = (int*)malloc(gathered_count * sizeof(int));

    // do gatherv
    MPI_Allgatherv(array, send_count, MPI_INT,
		   gathered_array, recv_counts, displs, MPI_INT,
		   MPI_COMM_WORLD);

    //  print_array(gathered_array, gathered_count, "Gathered array: ");

    free(array);
    free(recv_counts);
    free(displs);
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
