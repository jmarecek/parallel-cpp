void multiply_blocks(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C) {
#pragma omp declare reduction(vec_int_plus : std::vector<int> : std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<int>())) initializer(omp_priv = omp_orig)

    const int ROWS_IN_BLOCK = 10;
    const int BLOCKS_IN_ROW = ROWS/ROWS_IN_BLOCK;
    int tmp;

#pragma omp parallel for collapse(2) num_threads(thread_count) reduction(vec_int_plus : C) private(tmp)
    for (int br1=0; br1<BLOCKS_IN_ROW; br1++) {
        for (int bb=0; bb<BLOCKS_IN_ROW; bb++) {
            for (int bc2 = 0; bc2 < BLOCKS_IN_ROW; bc2++) {
                for (int r = br1 * ROWS_IN_BLOCK; r < (br1 + 1) * ROWS_IN_BLOCK; r++) {
                    for (int c = bc2 * ROWS_IN_BLOCK; c < (bc2 + 1) * ROWS_IN_BLOCK; c++) {
                        tmp = 0;
                        for (int k = 0; k < ROWS_IN_BLOCK; k++) {
                            tmp += A[r * COLS + (k + bb*ROWS_IN_BLOCK)] * B[(bb*ROWS_IN_BLOCK + k) * COLS + c];
                        }
                        C[r * COLS + c] += tmp;
                    }
                }
            }
        }
    }
}
