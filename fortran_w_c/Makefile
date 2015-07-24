FC = gfortran
CC = gcc
FLD = gfortran
CLD = gcc
LIBPATH = /usr/local/lib/gcc/5
LIBS = -lgfortran

.SUFFIXES : .f90 .c

TARGET = ftest ctest

FOBJ = simple_mod.o funcs.o
COBJ =
MOBJ = fmain.o cmain.o

all: $(TARGET)

%.o: %.mod

.f90.o:
	$(FC) -Wall -c $<

.c.o:
	$(CC) -Wall -c $<

ftest: $(FOBJ) fmain.o
	$(FLD) -o $@ $^

ctest: $(FOBJ) $(COBJ) cmain.o
	$(CLD) -L$(LIBPATH) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(FOBJ) $(COBJ) $(MOBJ) simple.mod
