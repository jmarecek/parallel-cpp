#include <iostream>
#include <omp.h>
#include <syncstream>

int main() {

#pragma omp parallel default(none)
  {
    int iam = omp_get_thread_num();
    int nt = omp_get_num_threads();
    std::osyncstream(std::cout) << iam << "/" << nt << std::endl;
  }

  return 0;
}
