#include <stdio.h>
#include <stdlib.h>
#include "update.h"

int
increment_one(const int val)
{
    return val + 1;
}

int
main()
{
    char *update_version = version();
    printf("Version: %s\n", update_version);

    size_t n = 10;
    int *vals = (int *)malloc(sizeof(int) * (size_t)n);
    for (size_t i = 0; i < n; i++) {
        vals[i] = (int)i + 1;
    }
    printf("Input Array\n");
    print_values(vals, n);

    update_values(vals, n, increment_one);
    printf("Output Array\n");
    print_values(vals, n);

    free(vals);
    return 0;
}
