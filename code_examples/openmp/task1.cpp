#include <iostream>
#include <syncstream>
#include "omp.h"

const int thread_count = 4;

void work() {
    int iam = omp_get_thread_num();
    int nt = omp_get_num_threads();
    std::osyncstream(std::cout) << "Thread " << iam << " of " << nt << std::endl;
}

int main(int argc, char* argv[]) {
#pragma omp parallel num_threads(thread_count)
  {
#pragma omp single
    {
      work();
#pragma omp task
      work();
    }
  }
}