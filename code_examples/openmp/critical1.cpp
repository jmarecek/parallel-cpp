const int thread_count = 2;
int main(int argc, char* argv[]) {
    int a = 42, b = 1;
#pragma omp parallel num_threads(thread_count) shared(a) private(b)
    {
        b = omp_get_thread_num()+2;
#pragma omp critical
        {
            a = a / b;
            std::cout << "Variable 'b' = " << b << " by thread " << (omp_get_thread_num()) << std::endl;
            std::cout << "Variable 'a' = " << a << " by thread " << (omp_get_thread_num()) << std::endl;
        }
    }
    std::cout << "Variable 'a' = " << a << " after omp " << std::endl;
    std::cout << "Variable 'b' = " << b << " after omp " << std::endl;
    return 0;
}
