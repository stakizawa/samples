#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int type_size;

  MPI_Init(&argc, &argv);

  printf("MPI_Request:   %d\n", sizeof(MPI_Request));

  MPI_Type_size(MPI_PACKED, &type_size);
  printf("MPI_PACKED:   %d\n", type_size);

  MPI_Type_size(MPI_BYTE, &type_size);
  printf("MPI_BYTE:   %d\n", type_size);

  MPI_Finalize();
  return 0;
}
