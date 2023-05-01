#include "omp.h"
#include <iostream>
#include <syncstream>

int main() {

  int i = 0;

#pragma omp parallel
  {

#pragma omp section
    {
      int j;
#pragma omp atomic
      do {
        j = i;
      } while (j == 0);
      std::osyncstream(std::cout) << j << std::endl;
    }
#pragma omp section
    {
#pragma omp atomic
      i = 1;
    }
  }
  return 0;
}