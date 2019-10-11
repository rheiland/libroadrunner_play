/*
clang++ -Xpreprocessor -fopenmp -m64 -std=c++11 -L/usr/local/opt/libomp/lib -lomp omp_hello.cpp -o hello_cpp 
*/

#include <iostream>
#include <omp.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;

  omp_set_num_threads(11);

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();
  std::cerr << "Hello World from thread = " << tid << std::endl;

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    std::cerr << "num  threads = " << nthreads << std::endl;
    }

  }  /* All threads join master thread and disband */
}
