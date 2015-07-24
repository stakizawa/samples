MPICC=mpicc
MPIRUN=mpirun
CFLAGS=

.PHONY: all clean

all: spawn_child spawn_shell_asis spawn_shell_wrap_mpi \
	spawn_shell_mpi sleep_mpi

spawn_child: spawn_child.c
	$(MPICC) $(CFLAGS) -o $@ $<

sleep_mpi: sleep_mpi.c
	$(MPICC) $(CFLAGS) -o $@ $<

spawn_shell_asis: spawn_shell.c
	$(MPICC) $(CFLAGS) -DSHELL_ASIS -o $@ $<

spawn_shell_mpi: spawn_shell.c
	$(MPICC) $(CFLAGS) -o $@ $<

spawn_shell_wrap_mpi: spawn_shell.c
	$(MPICC) $(CFLAGS) -DMPI_WRAP -o $@ $<

run_spawn_shell_asis: spawn_shell_asis
	$(MPIRUN) -np 2 ./spawn_shell_asis

run_spawn_shell_mpi: spawn_shell_mpi spawn_child
	$(MPIRUN) -np 2 ./spawn_shell_mpi

run_spawn_shell_wrap_mpi: spawn_shell_wrap_mpi sleep_mpi
	$(MPIRUN) -np 2 ./spawn_shell_wrap_mpi

clean:
	rm -f spawn_child spawn_shell_asis spawn_shell_wrap_mpi spawn_shell_mpi
	rm -f sleep_mpi
