FC = mpif90
CC = mpicc
FLD = mpif90
CLD = mpicc
LIBS = -lmpi_mpifh

.SUFFIXES : .f90 .c

 TARGET = ftest ctest

FOBJ = simple_mod.o funcs.o
MOBJ = fmain.o cmain.o

all: $(TARGET)

%.o: %.mod

.f90.o:
	$(FC) -Wall -c $<

.c.o:
	$(CC) -Wall -c $<

ftest: $(FOBJ) fmain.o
	$(FLD) -o $@ $^

ctest: $(FOBJ) cmain.o
	$(CLD) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(FOBJ) $(MOBJ) simple.mod
