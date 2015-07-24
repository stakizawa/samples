module simple
  use mpi
  implicit none
contains
  subroutine fetch_mpi_param(comm, nprocs, rank)
    integer :: comm, nprocs, rank
    integer :: ierr
    call MPI_COMM_SIZE(comm, nprocs, ierr)
    call MPI_COMM_RANK(comm, rank, ierr)
  end subroutine fetch_mpi_param
end module simple
