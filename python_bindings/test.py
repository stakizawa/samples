from ctypes import *

class Test:
    def __init__(self):
        mod_test = CDLL('./test.so')
        self.sum = mod_test.sum
        self.sub = mod_test.sub

        self.print_calc = mod_test.print_calc
        self.print_calc.restype = None

        CALCFUNC = CFUNCTYPE(c_int, c_int, c_int)
        self.mul_func = CALCFUNC(self.mul)

        self.CFuncPtr = type(mod_test.sum)

    def mul(self, a, b):
        return a * b

    def print_calc_wrap(self, a, b, func):
        if isinstance(func, self.CFuncPtr):
            print 'C Function Pointer Type'
        else:
            print 'Other Type'
        #self.print_calc(a, b, func)


####### main
t = Test()
a = 10
b = 5
print "Test for calling c functions"
print "%d + %d = %d" % (a, b, t.sum(a,b))
print "%d - %d = %d" % (a, b, t.sub(a,b))
print "%d * %d = %d" % (a, b, t.mul(a,b))
print

print "Test for calling a c functions that callback c and python functions"
t.print_calc(a, b, t.sum)
t.print_calc(a, b, t.sub)
t.print_calc(a, b, t.mul_func)
print

print "Test for checking C Function Pointer Type"
t.print_calc_wrap(a, b, t.sum)
t.print_calc_wrap(a, b, t.sub)
t.print_calc_wrap(a, b, t.mul_func)
