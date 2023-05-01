bool compare_swap(std::vector<int> &vector_to_sort, const int &val1, const int &val2) {
  if (vector_to_sort[val1] > vector_to_sort[val2]) {
    std::iter_swap(vector_to_sort.begin() + val1, vector_to_sort.begin() + val2);
    return true;
  }
  return false;
}

void bubble(std::vector<int> &vector_to_sort, int from, int to) {
  bool change = true;
  while (change) {
    change = false;
    for (int i = from + 1; i < to; i++) {
      change |= compare_swap(vector_to_sort, i - 1, i);
    }
  }
}
