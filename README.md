# Paralle-Matrix-Multiplication
Matrix multiplication using parallel programming in C (Pthrea and OpenMP) along with a sequential approach on Windows.
The three programs print the time it took to multiply the two square matrices of given size. Use matrix sizes above 500 for better reults. **Keep the number of threads equal to the number of logical processors on your CPU.** 

## PThread for Windows
To use `Pthread.h` on Windows(Since it is Unix only) used a replacement library avaliable at [POSIX Thraeds](http://sourceware.org/pthreads-win32/). The native Windows threading library is `Windows.h` which works abit different than Pthreads.
