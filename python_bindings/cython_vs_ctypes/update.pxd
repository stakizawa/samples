cdef extern from 'update.h':
    void update_values(int *vals, size_t count, int (*update_func)(const int))
    void print_values(int *vals, size_t count)
    char *version()
