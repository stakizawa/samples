      PROGRAM p2p
C Run with two processes
      include 'mpif.h'
      INTEGER err, rank, size
      real data(1)
      integer status(MPI_STATUS_SIZE)
      CALL MPI_INIT(err)
      CALL MPI_COMM_RANK(MPI_COMM_WORLD, rank, err)
      CALL MPI_COMM_SiZE(MPI_COMM_WORLD, size, err)

      data = 0.0
      if (rank.eq.0) then
         data=100.0
         call MPI_SEND(data, 1, MPI_REAL, 1, 55, MPI_COMM_WORLD, err)
      else if (rank.eq.1) then
         call MPI_RECV(data, 1, MPI_REAL, 0, 55,
     &        MPI_COMM_WORLD, status, err)
      end if
      print *, "Rank[", rank, "] data=",data

      call MPI_FINALIZE(err)
      end
