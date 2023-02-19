#include <iostream>
#include <syncstream>
#include <omp.h>

int main() {

#pragma omp parallel private(iam,nt)
{
        iam = omp_get_thread_num();
        nt =  omp_get_num_threads();
	std::osyncstream(std::cout) << iam << "/" << nt << std::endl;
}
	return 0;
}