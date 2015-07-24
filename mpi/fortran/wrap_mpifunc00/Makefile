CC	= mpicc
FC	= mpif90
CC_FLAG	= -g -Wall
FC_FLAG	= -g -Wall -I/usr/local/include -L.

all: libpms.a main

.SUFFIXES:	.f
.SUFFIXES:	.c

main: send.o
	$(FC) $(FC_FLAG) -o $@ $^ -lmpe_f2cmpi -lpms

send: send.o
	$(FC) $(FC_FLAG) -o $@ $^

.f.o:
	$(FC) $(FC_FLAG) -c $<

.c.o:
	$(CC) $(CC_FLAG) -c $<

libpms.a: profile_mpi_send.o
	ar cr $@ $^
	ranlib $@

clean:
	-rm -f send main libpms.a *.o *~

run:
	mpiexec -n 2 ./main

run_send:
	mpiexec -n 2 ./send
