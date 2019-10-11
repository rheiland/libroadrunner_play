/*
clang -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include/rr/C -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner_c_api  -L/usr/local/opt/libomp/lib -lomp omp_hello.c -o omp_hello
vs.
clang -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include/rr/C -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner_c_api  -fopenmp=lomp -L/usr/local/opt/libomp/lib -lomp omp_hello.c -o omp_hello

clang -I/Users/heiland/dev/roadrunner-osx-10.9-cp36m/include/rr/C -L/Users/heiland/dev/roadrunner-osx-10.9-cp36m/lib -lroadrunner_c_api  /usr/local/opt/libomp/lib/libomp.dylib omp_hello.c -o omp_hello

/usr/local/opt/lib/libomp.dylib

vs.
gcc-9 omp_hello.c -fopenmp
--> a.out
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;

  omp_set_num_threads(3);

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();
  printf("Hello World from thread = %d\n", tid);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and disband */
}
