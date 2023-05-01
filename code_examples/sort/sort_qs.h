void qs(std::vector<int> &vector_to_sort, int from, int to) {
  if (to - from <= base_size) {
    std::sort(vector_to_sort.begin() + from, vector_to_sort.begin() + to);
    return;
  }

  // cf. the pivot (vector_to_sort[from])
  int part2_start = partition(vector_to_sort, from, to, vector_to_sort[from]);

  if (part2_start - from > 1) {
#pragma omp task shared(vector_to_sort) firstprivate(from, part2_start)
    {
      qs(vector_to_sort, from, part2_start);
    }
  }
  if (to - part2_start > 1) {
    qs(vector_to_sort, part2_start, to);
  }
}