import ctypes

class Updater(object):
    def __init__(self):
        super(Updater, self).__init__()
        mod_update = ctypes.CDLL('./libupdate.so')

        self.UpdateFunc = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_int)

        self._update_values = mod_update.update_values
        self._update_values.argtypes = [ctypes.POINTER(ctypes.c_int),
                                        ctypes.c_size_t, self.UpdateFunc]
        self._update_values.restype = None

        self._print_values = mod_update.print_values
        self._print_values.argtypes = [ctypes.POINTER(ctypes.c_int),
                                       ctypes.c_size_t]
        self._print_values.restype = None

    def update(self, lst, f=None):
        if f == None:
            f = lambda x: 0
        f_inc = self.UpdateFunc(f)
        array = self._to_int_array(lst)
        self._update_values(array, ctypes.c_size_t(len(lst)), f_inc)
        for i in range(len(lst)):
            lst[i] = array[i]

    def print_values(self, lst):
        array = self._to_int_array(lst)
        self._print_values(array, ctypes.c_size_t(len(lst)))

    def increment_one(self, val):
        return val + 1

    def increment_byself(self, val):
        return val + val

    def decrement_one(self, val):
        return val - 1

    def _to_int_array(self, lst):
        IntArray = ctypes.c_int * len(lst)
        return IntArray(*lst)
