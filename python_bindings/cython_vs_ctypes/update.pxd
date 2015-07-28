cdef extern from 'update.h':
    void print_values(int *vals, size_t count)
    char *version()
