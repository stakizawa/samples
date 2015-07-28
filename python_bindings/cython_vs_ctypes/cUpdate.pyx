from libc.stdlib cimport malloc, free
cimport update

class Updater(object):
    def __init__(self):
        super(Updater, self).__init__()

    def print_values(self, ary):
        cdef int *cary = <int*>malloc(sizeof(int) * len(ary))
        for i in range(len(ary)):
            cary[i] = ary[i]
        update.print_values(cary, len(ary))
        free(cary)

    def version(self):
        return update.version()
