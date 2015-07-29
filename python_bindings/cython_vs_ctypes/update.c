#include <stdio.h>
#include "update.h"

void
update_values(int *vals, size_t count, update_func_t f)
{
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < count; i++) {
        vals[i] = f(vals[i]);
    }
}

void
print_values(int *vals, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        printf("%d ", vals[i]);
    }
    printf("\n");
}

char *
version()
{
    return VERSION;
}
