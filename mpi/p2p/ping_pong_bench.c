/*
 * Ping-pong benchmark using MPI.
 * This program works with just two processes.
 * In this program, first rank 0 sends a 0-byte MPI message to rank 1
 * and then rank 1 sends back 0-byte MPI message to rank 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N_WARMUP 100
#define N_ITERATION 1000

int ping_pong();
double single_ping_pong();

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

  int i;

  // warm up
  for (i = 0; i < N_WARMUP; i++) {
    single_ping_pong();
  }

  // benchmark main
  double max = 0, min = 10, sum = 0;
  for (i = 0; i < N_ITERATION; i++) {
    double time = single_ping_pong();
    if (myid == 0) {
      sum += time;
      if (time > max) max = time;
      if (time < min) min = time;
    }
  }

  if (myid == 0) {
    printf("warmup count,%d\n", N_WARMUP);
    printf("iteration count,%d\n", N_ITERATION);
    printf("min,%0.9f\n", min);
    printf("max,%0.9f\n", max);
    printf("avg,%0.9f\n", (sum / N_ITERATION));
  }

  return 0;
}

double single_ping_pong()
{
  MPI_Status status;

  MPI_Barrier(MPI_COMM_WORLD);
  double stime = MPI_Wtime();

  if (myid == 0) {
    MPI_Send(NULL, 0, MPI_INT, 1, 1000, MPI_COMM_WORLD);
    MPI_Recv(NULL, 0, MPI_INT, 1, 1001, MPI_COMM_WORLD, &status);
  } else {
    MPI_Recv(NULL, 0, MPI_INT, 0, 1000, MPI_COMM_WORLD, &status);
    MPI_Send(NULL, 0, MPI_INT, 0, 1001, MPI_COMM_WORLD);
  }

  return MPI_Wtime() - stime;
}
