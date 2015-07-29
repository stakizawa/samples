CC = gcc

OBJS = update.o cmain.o
LIB = libupdate.so
CYLIB = cUpdate.so

PYINC = $(shell python -c \
	"from distutils import sysconfig; print(sysconfig.get_python_inc())")

.PHONY: all clean

all: $(LIB) cmain $(CYLIB)

.c.o:
	$(CC) -Wall -fPIC -c $<

$(LIB): update.o
	$(CC) -shared -o $@ $<

cmain: $(LIB) cmain.o
	$(CC) -o $@ $^ -L. -lupdate

$(CYLIB): update.o update.pxd cUpdate.pyx
	cython -o cUpdate.c cUpdate.pyx
	$(CC) -I$(PYINC) -fPIC -c cUpdate.c
	$(CC) -undefined dynamic_lookup -shared -o $@ update.o cUpdate.o

clean:
	-rm -f $(LIB) $(OBJS) cmain *.pyc
	-rm -f $(CYLIB) cUpdate.c cUpdate.o
