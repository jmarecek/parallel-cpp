void multiply(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C) {
#pragma omp declare reduction(vec_int_plus : std::vector<int> : \
                    std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<int>())) \
                    initializer(omp_priv = omp_orig)
    int tmp;
#pragma omp parallel for collapse(2) num_threads(thread_count) reduction(vec_int_plus : C)
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            tmp = 0;
            for (int k=0; k<ROWS; k++) {
                tmp += A[i * COLS + k] * B[k * COLS + j];
            }
            C[i * COLS + j] += tmp;
        }
    }
}
