void gauss_par(std::vector<double> &A) {
#pragma omp declare reduction(vec_int_plus           \
                              : std::vector <double> \
                              : std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus <double>())) initializer(omp_priv = omp_orig)
  for (int i = 0; i < ROWS; i++) {
    // Make all rows below this one 0 in current column
#pragma omp parallel for num_threads(thread_count)
    for (int k = i + 1; k < ROWS; k++) {
      double c = -A[k * COLS + i] / A[i * COLS + i];
      for (int j = i; j < ROWS; j++) {
        if (i == j) {
          A[k * COLS + j] = 0;
        } else {
          A[k * COLS + j] += c * A[i * COLS + j];
        }
      }
    }
  }
}
