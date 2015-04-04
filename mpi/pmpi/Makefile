CC	= mpicc
CC_FLAG	= -g -Wall -L.

all: libpms.a main

.SUFFIXES:	.c

main: send.o
	$(CC) $(CC_FLAG) -o $@ $^ -lpms

.c.o:
	$(CC) $(CC_FLAG) -c $<

libpms.a: profile_mpi_send.o
	ar cr $@ $^
	ranlib $@

clean:
	-rm -f main libpms.a profile_mpi_send.o send.o *~

run:
	mpiexec -n 3 ./main

