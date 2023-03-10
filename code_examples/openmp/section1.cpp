#include <iostream>
#include <syncstream>
#include "omp.h"

const int thread_count = 2;

void work(const int& i) {
  int iam = omp_get_thread_num();
  std::osyncstream(std::cout) << "Hello from work(" << i << ") by t = " << iam << std::endl;
}

int main(int argc, char* argv[]) {
#pragma omp parallel num_threads(thread_count)
  {
#pragma omp sections
    {
#pragma omp section
      { work(1); }
#pragma omp section
      { work(2); }
    }
  }
  return 0;
}
