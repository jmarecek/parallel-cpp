#include <iostream>
#include <syncstream>
#include "omp.h"

int main() {
#pragma omp parallel 
  {
    std::osyncstream(std::cout) << "Thread" << omp_get_thread_num() << std::endl;

#pragma omp for
    for (int i=0; i<10; i++)
      std::osyncstream(std::cout) << "For i = " << i << " in t = " << omp_get_thread_num() << std::endl;
    }

    std::osyncstream(std::cout) << "Main thread\n";
    return 0;
}
