# README #

## Programs ##

Programs for testing the library.

* cmain.c
  * A main program implemented in C
* cymain.py
  * A main program that tests the Cython library
* cymain_omp.py
  * A main program that tests the OpenMP-enabled Cython library
* pymain.py
  * A main program that tests wrapped by ctypes library

Programs for benchmarking.

* cybench.py
  * A benchmark program for Cython implementation without OpenMP
* cybench_omp.py
  * A benchmark program for Cython implementation with OpenMP
* pybench.py
  * A benchmark program for ctypes implementation with/without OpenMP

## How to Build ##

* On Mac

    $ make -f makefile.mac

* On Linux

    $ make -f makefile.linux

* On Linux with OpenMP

    $ make -f makefile.linux_openmp
