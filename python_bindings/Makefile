CC = gcc

objs = test.so

.PHONY: all clean

all: test.so

test.so: test.c
	$(CC) -shared -fPIC -o $@ $<

clean:
	-rm -f $(objs)
	-rm -f a.out
