subroutine fetch_mpi_param_nonmod(comm, nprocs, rank)
  use mpi
  implicit none
  integer :: comm, nprocs, rank
  integer :: ierr
  call MPI_COMM_SIZE(comm, nprocs, ierr)
  call MPI_COMM_RANK(comm, rank, ierr)
end subroutine fetch_mpi_param_nonmod
