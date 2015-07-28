#ifndef UPDATE_H
#define UPDATE_H

#include <stdio.h>

#define VERSION "0.1.0"

typedef int (*update_func_t)(const int);

void update_values(int *, size_t, update_func_t);
void print_values(int *, size_t);
char *version();

#endif
