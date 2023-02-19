#include <iostream>
#include <syncstream>
#include <thread>
#include "omp.h"

int work() {
    return 0;
}

int main() {
    int sum = 0; 
#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < nbodies; i++) sum += work();
}