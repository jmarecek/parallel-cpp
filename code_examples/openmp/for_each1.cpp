// Please compile with -std=c++2b -fopenmp

#include "omp.h"
#include <iostream>
#include <syncstream>

int main(int argc, char *argv[]) {
  std::cout << "Hello from the main thread\n";

#pragma omp parallel for
  for (int i = 0; i < 10; i++)
    std::osyncstream(std::cout) << "Item " << i << " is processed by thread" << omp_get_thread_num() << std::endl;
  return 0;
}
                                                                                                                                                                                                                                                                                                                                                                     