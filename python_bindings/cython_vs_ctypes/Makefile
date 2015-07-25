CC = gcc

OBJS = update.o cmain.o
LIB = libupdate.so

.PHONY: all clean

all: $(LIB) cmain

.c.o:
	$(CC) -Wall -fPIC -c $<

$(LIB): update.o
	$(CC) -shared -o $@ $<

cmain: $(LIB) cmain.o
	$(CC) -o $@ $^ -L. -lupdate

clean:
	-rm -f $(LIB) $(OBJS) cmain *.pyc
