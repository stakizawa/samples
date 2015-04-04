/*
 * This works with any number of processes.
 * Even numbered process sends a message to add (id+1) numbered process.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

void print_comm(MPI_Comm comm);
void simple_split(MPI_Comm comm, MPI_Comm *newcomm, char *name);
void chk_rnk_correspondence(MPI_Comm from, MPI_Comm to);

int main(int argc, char *argv[]) {
  MPI_Comm comm1, comm2;

  MPI_Init(&argc, &argv);

  // print MPI_COMM_WORLD
  //print_comm(MPI_COMM_WORLD);

  // split MPI_COMM_WORLD
  simple_split(MPI_COMM_WORLD, &comm1, "half");
  //print_comm(comm1);

  // check MPI_Group_translate_ranks (against MPI_COMM_WORLD)
  chk_rnk_correspondence(comm1, MPI_COMM_WORLD);

  // split comm1
  simple_split(comm1, &comm2, "quarter");
  //print_comm(comm2);

  // check MPI_Group_translate_ranks (against MPI_COMM_WORLD)
  chk_rnk_correspondence(comm2, MPI_COMM_WORLD);

  MPI_Finalize();
  return 0;
}

void print_comm(MPI_Comm comm) {
  int size, myid, name_len;
  char name[MPI_MAX_OBJECT_NAME];
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &myid);
  MPI_Comm_get_name(comm, name, &name_len);
  printf("Comm[%s,%d]: %d\n", name, size, myid);
}

void simple_split(MPI_Comm comm, MPI_Comm *newcomm, char *name) {
  int size, myid;
  int new_size, split_color, split_key;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &myid);

  new_size = size / 2;
  split_color = myid / new_size;
  split_key   = myid % new_size;

  MPI_Comm_split(comm, split_color, split_key, newcomm);
  MPI_Comm_set_name(*newcomm, name);
}

void chk_rnk_correspondence(MPI_Comm from, MPI_Comm to) {
  MPI_Group from_grp, to_grp;
  int from_size, *f_ranks, *t_ranks;
  char from_name[MPI_MAX_OBJECT_NAME];
  char to_name[MPI_MAX_OBJECT_NAME];
  int f_len, t_len;
  int i;

  MPI_Comm_group(from, &from_grp);
  MPI_Comm_group(to, &to_grp);
  MPI_Comm_get_name(from, from_name, &f_len);
  MPI_Comm_get_name(to, to_name, &t_len);
  MPI_Comm_size(from, &from_size);

  f_ranks = (int*)malloc(from_size * sizeof(int));
  t_ranks = (int*)malloc(from_size * sizeof(int));
  for (i = 0; i < from_size; i++) f_ranks[i] = i;

  MPI_Group_translate_ranks(from_grp, from_size, f_ranks, to_grp, t_ranks);

  for (i = 0; i < from_size; i++) {
    printf("Comm[%s]:%d -> Comm[%s]:%d\n", from_name, f_ranks[i],
	   to_name, t_ranks[i]);
  }
}
