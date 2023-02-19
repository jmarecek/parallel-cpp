#include <chrono>
#include <iostream>
#include "omp.h"

int main() {
	using namespace std::chrono_literals;
	omp_lock_t lock;
	omp_init_lock(&lock);

#pragma omp parallel num_threads(4)
	omp_set_lock(&lock); // mutual exclusion (mutex)
	std::cout << "Locked in " << omp_get_thread_num() << std::endl;
	std::this_thread::sleep_for(1s);
	std::cout << "Released in " << omp_get_thread_num() << std:: endl;
	omp_unset_lock(&lock);
}
	omp_destroy_lock(&lock);
}