void parallel_bubble(std::vector<int> &vector_to_sort, unsigned int from, unsigned int to) {
  while (change) {
    change = false;
#pragma omp parallel for num_threads(thread_count) schedule(static) shared(vector_to_sort) reduction(| \
                                                                                                     : change)
    for (int i = from + 1; i < to; i += 2) {
      change |= compare_swap(vector_to_sort, i - 1, i);
    }

#pragma omp parallel for num_threads(thread_count) schedule(static) shared(vector_to_sort) reduction(| \
                                                                                                     : change)
    for (int i = from + 2; i < to; i += 2) {
      change |= compare_swap(vector_to_sort, i - 1, i);
    }
  }
}
