from libc.stdlib cimport malloc, free
cimport update

cdef int update_callback(const int x) except *:
    return update_fn(x)

cdef class Updater(object):
    def __init__(self):
        super(Updater, self).__init__()

    def print_values(self, lst):
        cdef int cary_size = len(lst)
        cdef int *cary = <int*>malloc(sizeof(int) * cary_size)
        if cary == NULL:
            raise MemoryError('Unable to allocate array.')
        for i in range(cary_size):
            cary[i] = lst[i]
        with nogil:
            update.print_values(cary, cary_size)
        free(cary)

    def update(self, lst, f=None):
        global update_fn
        cdef int *cary = <int*>malloc(sizeof(int) * len(lst))
        if cary == NULL:
            raise MemoryError('Unable to allocate array.')
        for i in range(len(lst)):
            cary[i] = lst[i]

        if f == None:
            f = lambda x: 0
        update_fn = f
        update.update_values(cary, len(lst), update_callback)

        for i in range(len(lst)):
            lst[i] = cary[i]
        free(cary)

    def increment_one(self, val):
        return val + 1

    def increment_byself(self, val):
        return val + val

    def decrement_one(self, val):
        return val - 1

    def version(self):
        return update.version()
