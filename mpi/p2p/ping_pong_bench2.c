/*
 * Ping-pong benchmark using MPI.
 * This program works with just two processes.
 * In this program, first rank 0 sends verious size MPI message to rank 1
 * and then rank 1 sends back the same size MPI message to rank 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N_WARMUP 100
#define N_ITERATION 100
#define MAX_MSG 134217728 // 128MB in int


int ping_pong();
double single_ping_pong(int);
void iterate_single_ping_pong(int);

int myid, comm_size;

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  int result = ping_pong();

  MPI_Finalize();
  return result;
}

int ping_pong()
{
  if (comm_size != 2) {
    if (myid == 0) {
      fprintf(stderr, "Run this benchmark with two processes\n");
    }
    return -1;
  }

  if (myid == 0) {
    printf("warmup count,%d\n", N_WARMUP);
    printf("iteration count,%d\n", N_ITERATION);
    printf("maximum message size,%d\n", MAX_MSG);
    printf("\n");
    printf("Size,Min,Max,Average\n");
  }

  int i;

  // warm up
  for (i = 0; i < N_WARMUP; i++) {
    single_ping_pong(0);
  }

  // benchmark main
  iterate_single_ping_pong(0);
  for (i = 1; i <= MAX_MSG; i *= 2) {
    iterate_single_ping_pong(i);
  }

  return 0;
}

void iterate_single_ping_pong(int size) {
  int i;
  double max = 0, min = MAX_MSG, sum = 0;

  for (i = 0; i < N_ITERATION; i++) {
    double time = single_ping_pong(size);
    if (myid == 0) {
      sum += time;
      if (time > max) max = time;
      if (time < min) min = time;
    }
  }

  if (myid == 0) {
    printf("%ld,%0.9f,%0.9f,%0.9f\n", (size * sizeof(int)),
	   min, max, (sum / N_ITERATION));
  }
}

double single_ping_pong(int size)
{
  MPI_Status status;
  int *data1, *data2, *data;
  int i;

  data1 = (int*)calloc(size, sizeof(int));
  data2 = (int*)calloc(size, sizeof(int));
  if (myid == 0) data = data1;
  else data = data2;
  for (i = 0; i < size; i++) {
    data[i] = myid;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  double stime = MPI_Wtime();

  if (myid == 0) {
    MPI_Send(data1, size, MPI_INT, 1, 1000, MPI_COMM_WORLD);
    MPI_Recv(data2, size, MPI_INT, 1, 1001, MPI_COMM_WORLD, &status);
  } else {
    MPI_Recv(data1, size, MPI_INT, 0, 1000, MPI_COMM_WORLD, &status);
    MPI_Send(data2, size, MPI_INT, 0, 1001, MPI_COMM_WORLD);
  }

  double etime = MPI_Wtime();

  free(data1);
  free(data2);
  return etime - stime;
}
