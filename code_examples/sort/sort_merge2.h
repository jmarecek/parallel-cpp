void ms_parallel(std::vector<int> &vector_to_sort, int from, int to) {
  if (to - from <= 1) {
    return;
  }
  int middle = (to - from) / 2 + from;

  ms_serial(vector_to_sort, from, middle);
  ms_serial(vector_to_sort, middle, to);
  std::inplace_merge(vector_to_sort.begin() + from, vector_to_sort.begin() + middle, vector_to_sort.begin() + to);
}

void ms(std::vector<int> &vector_to_sort, int from, int to) {
  if (to - from <= base_size) {
    ms_serial(vector_to_sort, from, to);
    return;
  }
  int middle = (to - from) / 2 + from;

#pragma omp task shared(vector_to_sort) firstprivate(from, middle)
  ms(vector_to_sort, from, middle);

  ms(vector_to_sort, middle, to);

#pragma omp taskwait
  std::inplace_merge(vector_to_sort.begin() + from, vector_to_sort.begin() + middle, vector_to_sort.begin() + to);
}
