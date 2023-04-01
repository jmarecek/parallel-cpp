...
// data has to be ordered by columns in memory
for (int i = 0; i < COLS; i++) {
            x[i] = rand() % 1000;
            for (int j = 0; j < ROWS; j++) {
                A[i * ROWS + j] = rand() % 1000;
            }
        }
...

void multiply_column(std::vector<int> &A, std::vector<int> &x, std::vector<int> &y) {
#pragma omp declare reduction(vec_int_plus : std::vector<int> : \
                    std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<int>())) \
                    initializer(omp_priv = omp_orig)

#pragma omp parallel for num_threads(thread_count) reduction(vec_int_plus : y)
    for ( int i = 0; i < COLS ; i ++) {
        for (int j = 0; j < ROWS; j++) {
            y[j] += A[i * ROWS + j]*x[i];
        }
    }
}
