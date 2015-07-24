#include <stdio.h>
#include "mpi.h"

int MPI_Send(void *buffer, const int count, MPI_Datatype datatype,
	     int dest, int tag, MPI_Comm comm)
{
  double t1, t2;
  t1 = MPI_Wtime();
  int result = PMPI_Send(buffer, count, datatype, dest, tag, comm);
  t2 = MPI_Wtime();
  fprintf(stderr, "MPI_Send time: %0.6f\n", (t2-t1));
  return result;
}
