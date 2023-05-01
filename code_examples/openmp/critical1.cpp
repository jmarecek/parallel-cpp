#include "omp.h"
#include <iostream>
#include <syncstream>

const int thread_count = 2;

int main() {
  int a = 42, b = 1;
#pragma omp parallel num_threads(thread_count) shared(a) private(b)
  {
    b = omp_get_thread_num() + 2;
#pragma omp critical
    {
      a = a / b;
      int t = omp_get_thread_num();
      std::osyncstream(std::cout) << "b = " << b << " in t = " << t << "\n";
      std::osyncstream(std::cout) << "b = " << a << " in t = " << t << "\n";
    }
  }
  std::osyncstream(std::cout) << "a = " << a << "\n";
  std::osyncstream(std::cout) << "b = " << b << "\n";
  return 0;
}