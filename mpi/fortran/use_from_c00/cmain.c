/*
  This is a test for calling fortran90 subroutines from C.
 */
#include <stdio.h>
#include <mpi.h>

void __simple_MOD_fetch_mpi_param(MPI_Fint *, int *, int *);
void fetch_mpi_param_nonmod_(MPI_Fint *, int *, int *);

int
main(int argc, char **argv)
{
    int nprocs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Fint comm_f = MPI_Comm_c2f(comm);

    __simple_MOD_fetch_mpi_param(&comm_f, &nprocs, &rank);
    printf("From module subroutine, this is %d in %d.\n", rank, nprocs);

    nprocs = -1;
    rank   = -1;
    printf("nprocs and rank are cleard: %d, %d\n", rank, nprocs);

    fetch_mpi_param_nonmod_(&comm_f, &nprocs, &rank);
    printf("From non-module subroutine, this is %d in %d.\n", rank, nprocs);

    MPI_Finalize();
    return 0;
}
