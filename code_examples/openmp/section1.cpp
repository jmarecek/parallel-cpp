#include <iostream>
#include <vector>
#include "omp.h"

const int thread_count = 2;

void method(const int& i) {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    std::cout << "Hello from method " << i << " by thread " << my_rank << std::endl;
}

int main(int argc, char* argv[]) {

#pragma omp parallel num_threads(thread_count)
    {
#pragma omp sections
        {
#pragma omp section
            { method(1); }
#pragma omp section
            { method(2); }
        }
    }

    return 0;
}
