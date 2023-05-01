void multiply(std::vector<int> &A, std::vector<int> &B, std::vector<int> &C) {
#pragma omp declare reduction(vec_int_plus        \
                              : std::vector <int> \
                              : std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus <int>())) initializer(omp_priv = omp_orig)

#pragma omp parallel for collapse(2) num_threads(thread_count) reduction(vec_int_plus \
                                                                         : C)
  for (int r1 = 0; r1 < ROWS; r1++) {
    for (int r2 = 0; r2 < ROWS; r2++) {
      for (int k = 0; k < ROWS; k++) {
        C[r1 * COLS + k] += A[r1 * COLS + r2] * B[r2 * COLS + k];
      }
    }
  }
}
