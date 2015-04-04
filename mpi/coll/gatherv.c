/*
 * This works with any number of processes.
 * process sends message whose size is "rank + 1"
 */
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_array(int *array, int count, const char *msg);
int gatherv();

int myid, size;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  gatherv();

  MPI_Finalize();
  return 0;
}

int gatherv() {
  int *array;
  int send_count;
  int *recv_counts, *displs;
  int *gathered_array, gathered_count;
  char output_msg[16];
  int i;

  // initialize arrays on each process
  send_count = myid + 1;
  array = (int*)malloc(send_count * sizeof(int));
  for (i = 0; i < send_count; i++) {
    array[i] = 100 + myid;
  }
  snprintf(output_msg, 16, "Rank[%d]: ", myid);
  print_array(array, send_count, output_msg);

  // initialize gathered_array on root
  if (myid == 0) {
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
  } else {
    gathered_count = -1;
    gathered_array = (void*)0;
    displs = (void*)0;
    recv_counts = (void*)0;
  }

  // do gatherv
  MPI_Gatherv(array, send_count, MPI_INT,
	      gathered_array, recv_counts, displs, MPI_INT,
	      0, MPI_COMM_WORLD);

  // print gathered array on root
  if (myid == 0) {
    print_array(gathered_array, gathered_count, "Gathered array: ");
  }

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
