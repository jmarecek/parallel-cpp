#include "omp.h"
#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::chrono_literals;

int main() {
  omp_lock_t lock;
  omp_init_lock(&lock);

#pragma omp parallel num_threads(4)
  {
    omp_set_lock(&lock); // mutual exclusion (mutex)
    std::osyncstream(std::cout) << "Locked in " << omp_get_thread_num() << std::endl;
    std::this_thread::sleep_for(1s);
    std::osyncstream(std::cout) << "Released in " << omp_get_thread_num() << std::endl;
    omp_unset_lock(&lock);
  }
  omp_destroy_lock(&lock);
}
