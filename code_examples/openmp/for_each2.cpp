#include <iostream>
#include <vector>
#include "omp.h"

int main(int argc, char* argv[]) {
#pragma omp parallel 
    {
        std::cout << "this is a line printed by thread" << omp_get_thread_num() << std::endl;

#pragma omp for
        for (int i=0; i<10; i++)
            std::cout << "for-loop line " << i << " printed by thread" << omp_get_thread_num() << std::endl;

    }

    std::cout << "Hello from the main thread\n";

    return 0;
}
