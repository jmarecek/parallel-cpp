#include <iostream>
#include <omp.h>
#include <syncstream>

int main() {

  omp_set_nested(1);
  int iam, nt;

#pragma omp parallel num_threads(2) default(none) private(iam, nt)
  {
    iam = omp_get_thread_num();
    nt = omp_get_num_threads();
    std::osyncstream(std::cout) << "L1: " << iam << "/" << nt << std::endl;

#pragma omp parallel num_threads(2) default(none) private(iam, nt)
    {
      iam = omp_get_thread_num();
      nt = omp_get_num_threads();
      std::osyncstream(std::cout) << "L2 " << iam << "/" << nt << std::endl;
    }
  }
  return 0;
}
