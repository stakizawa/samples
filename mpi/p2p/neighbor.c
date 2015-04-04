/* Neighbor benchmark by Endo */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int size;
int nx, ny; /* total process number */
int rank;
int ix, iy; /* my id */
int msgsize;
int niter;

int main_loop()
{
  int i;
  char *bufs[4];
  char *bufr[4];

  for (i = 0; i < 4; i++) {
    bufs[i] = calloc(msgsize, 1);
    bufr[i] = calloc(msgsize, 1);
  }

  for (i = 0; i < niter; i++) {
    MPI_Request req[4];
    MPI_Status stat;

    if (nx >= 2) {
      /* left and right */
      int rankp = rank-1;
      int rankn = rank+1;
      if (ix > 0) {
	MPI_Irecv(bufr[0], msgsize, MPI_BYTE, rankp, 100,
		  MPI_COMM_WORLD, &req[0]);
      }
      if (ix < nx-1) {
	MPI_Irecv(bufr[1], msgsize, MPI_BYTE, rankn, 101,
		  MPI_COMM_WORLD, &req[1]);
      }
      if (ix < nx-1) {
	MPI_Send(bufs[0], msgsize, MPI_BYTE, rankn, 100,
		 MPI_COMM_WORLD);
      }
      if (ix > 0) {
	MPI_Send(bufs[1], msgsize, MPI_BYTE, rankp, 101,
		 MPI_COMM_WORLD);
      }
      if (ix > 0) {
	MPI_Wait(&req[0], &stat);
      }
      if (ix < nx-1) {
	MPI_Wait(&req[1], &stat);
      }
    }

    /* up and down */
    if (ny >= 2) {
      int rankp = rank-nx;
      int rankn = rank+nx;
      if (iy > 0) {
	MPI_Irecv(bufr[2], msgsize, MPI_BYTE, rankp, 102,
		  MPI_COMM_WORLD, &req[2]);
      }
      if (iy < ny-1) {
	MPI_Irecv(bufr[3], msgsize, MPI_BYTE, rankn, 103,
		  MPI_COMM_WORLD, &req[3]);
      }
      if (iy < ny-1) {
	MPI_Send(bufs[2], msgsize, MPI_BYTE, rankn, 102,
		 MPI_COMM_WORLD);
      }
      if (iy > 0) {
	MPI_Send(bufs[3], msgsize, MPI_BYTE, rankp, 103,
		 MPI_COMM_WORLD);
      }
      if (iy > 0) {
	MPI_Wait(&req[2], &stat);
      }
      if (iy < ny-1) {
	MPI_Wait(&req[3], &stat);
      }
    }

    if (ix == 0 && iy == 0) {
      fprintf(stderr, "%d-th iteration finishes\n", i);
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);

  if (argc < 5) {
    fprintf(stderr, "Specify #proc-x, #proc-y, msg-size(bytes), #iteration\n");
    MPI_Finalize();
    exit(1);
  }

  nx = atoi(argv[1]);
  ny = atoi(argv[2]);
  msgsize = atoi(argv[3]);
  niter = atoi(argv[4]);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != nx*ny) {
    fprintf(stderr, "#processes is invalid (%d != %d * %d)\n",
	    size, nx, ny);
    MPI_Finalize();
    exit(1);
  }

  ix = rank % nx;
  iy = rank / nx;

  fprintf(stderr, "I'm %d,%d\n", ix, iy);

  main_loop();

  MPI_Finalize();
}
