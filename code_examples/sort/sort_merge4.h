#include <immintrin.h>

int main() {

  std::vector<int> vec1 = std::vector<int>(SIZE);
  std::vector<int> vec2 = std::vector<int>(SIZE);

  for (int i = 0; i < SIZE; i++) {
    vec1[i] = rand() % 10000;
    vec2[i] = rand() % 10000;
  }

  auto t_start = std::chrono::high_resolution_clock::now();

  __m256i v1;
  __m256i v2;
  __m256i r1, r2;

  for (int i = 0; i < SIZE; i += 8) {
    v1 = _mm256_loadu_si256((__m256i *)&vec1[i]);
    v2 = _mm256_loadu_si256((__m256i *)&vec2[i]);
    r1 = _mm256_min_epi32(v1, v2);
    r2 = _mm256_max_epi32(v1, v2);
    _mm256_storeu_si256((__m256i *)&vec1[i], r1);
    _mm256_storeu_si256((__m256i *)&vec2[i], r2);
  }

  auto t_end = std::chrono::high_resolution_clock::now();
  double elapsed = std::chrono::duration<double, std::milli>(t_end - t_start).count() / 1000.0;

  std::cout << "compared in " << elapsed << " s" << std::endl;
  return 0;
}
