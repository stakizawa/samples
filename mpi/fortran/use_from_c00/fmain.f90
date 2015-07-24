program fmain
  use mpi
  use simple
  implicit none
  integer ierr, nprocs, rank

  call MPI_INIT(ierr)

  call fetch_mpi_param(MPI_COMM_WORLD, nprocs, rank)
  ! call MPI_COMM_SIZE(MPI_COMM_WORLD, nprocs, ierr)
  ! call MPI_COMM_RANK(MPI_COMM_WORLD, rank, ierr)
  print '("From module subroutine, this is ", i2, " in ", i2, ".")', &
       rank, nprocs

  nprocs = -1
  rank   = -1
  print'("nprocs and rank are cleared: ", i2, ", ", i2)', rank, nprocs

  call fetch_mpi_param_nonmod(MPI_COMM_WORLD, nprocs, rank)
  print '("From non-module subroutine, this is ", i2, " in ", i2, ".")', &
       rank, nprocs

  call MPI_FINALIZE(ierr)
end program fmain
