/*
 * This works with any number of processes.
 */

#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int comm_size, myid;
  char proc_name[32];
  int proc_name_len;
  int pid, omp_tid;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Get_processor_name(proc_name, &proc_name_len);

  #pragma omp parallel
  { 
    pid = getpid();
    omp_tid = omp_get_thread_num();

    printf("%s:%02d:%07d:%02d\n", proc_name, myid, pid, omp_tid);
  }

  MPI_Finalize();
  return 0;
}
