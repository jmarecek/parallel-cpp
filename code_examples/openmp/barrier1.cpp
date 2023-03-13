#include <iostream>
#include <syncstream>
#include "omp.h"

void work() {
    std::osyncstream(std::cout) << "a";
#pragma omp barrier
    std::osyncstream(std::cout) << "A";
}

int main() {
#pragma omp parallel num_threads(5)
    work();
}