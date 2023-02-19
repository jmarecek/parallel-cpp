const int thread_count = 4;

void Hello() {
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    std::cout << "Hello from thread " << my_rank << " of " << thread_count << std::endl;
}

int main(int argc, char* argv[]) {
#pragma omp parallel num_threads(thread_count)
    {
#pragma omp single
        {
            Hello();
#pragma omp task
            Hello();
        }
    }
}
