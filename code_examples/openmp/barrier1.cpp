#include <iostream>
#include <syncstream>
#include <thread>
#include "omp.h"

void work() {
    std::osyncstream(std::cout) << n;
#pragma omp barrier
    std::osyncstream(std::cout) << n;
}

int main() {
#pragma omp parallel shared(5)
    work();
}

