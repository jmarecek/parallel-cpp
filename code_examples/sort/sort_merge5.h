int SIZE = 8;
std::vector<int> vec1 = std::vector<int>(SIZE);
for (int i = 0; i < SIZE; i++) {
  vec1[i] = rand() % 10000;
  std::cout << vec1[i] << " ";
}
__m128i mask_llhhllhh = _mm_set_epi32(0xffffffff, 0, 0xffffffff, 0);
__m128i mask_hhllhhll = _mm_set_epi32(0, 0xffffffff, 0, 0xffffffff);
__m128i v1;
__m128i v2;
__m128i r1, r2;
for (int i = 0; i < SIZE; i += 4) {
  v1 = _mm_loadu_si128((__m128i *)&vec1[i]);
  v2 = _mm_alignr_epi8(_mm_setzero_si128(), v1, 1 * 4);
  r1 = _mm_min_epi32(v1, v2);
  r1 = _mm_and_si128(r1, mask_hhllhhll);
  v2 = _mm_alignr_epi8(v1, _mm_setzero_si128(), 3 * 4);
  r2 = _mm_max_epi32(v1, v2);
  r2 = _mm_and_si128(r2, mask_llhhllhh);
  r1 = _mm_or_si128(r1, r2);
  _mm_storeu_si128((__m128i *)&vec1[i], r1);
}