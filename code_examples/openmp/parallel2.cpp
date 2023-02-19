#include <iostream>
#include <syncstream>
#include <omp.h>

int main() {

   omp_set_nested(1);

#pragma omp parallel num_threads(2) private(iam,nt)
{
        int iam = omp_get_thread_num();
        int nt =  omp_get_num_threads();
	std::osyncstream(std::cout) << "L1: " << iam << "/" << nt << std::endl;

#pragma omp parallel num_threads(2) private(iam,nt)
{
        iam = omp_get_thread_num();
        nt =  omp_get_num_threads();
        std::osyncstream(std::cout) << "L2 " << iam << "/" << nt << std::endl;
}
}
	return 0;
}