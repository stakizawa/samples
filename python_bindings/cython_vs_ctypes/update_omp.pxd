cdef extern from 'update.h':
    ctypedef int (*update_func_t)(const int) except *
    void update_values(int *vals, size_t count, update_func_t f) nogil
    void print_values(int *vals, size_t count) nogil
    char *version()

cdef extern from 'Python.h':
    void PyEval_InitThreads()
