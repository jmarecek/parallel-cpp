// Based on:
// https://www.openmp.org/wp-content/uploads/2021-10-20-Webinar-OpenMP-Offload-Programming-Introduction.pdf

void saxpy(float a, float* x, float* y, int sz, int num_blocks) {
#pragma omp target teams distribute parallel for simd \
  num_teams(num_blocks) map(to:x[0:sz]) map(tofrom:y[0:sz])
  for (int i = 0; i < sz; i++) {
    y[i] = a * x[i] + y[i];
  }
}