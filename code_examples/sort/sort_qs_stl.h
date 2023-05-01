template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) {
  if (first == last)
    return;
  std::size_t distance = std::distance(first, last);
  auto pivot = *std::next(first, distance / 2);
  ForwardIt middle1;
  ForwardIt middle2;
  if (distance < threshold) {
    middle1 = std::partition(std::execution::seq, first, last, [pivot](const auto &em) { return em < pivot; });
    middle2 = std::partition(std::execution::seq, middle1, last, [pivot](const auto &em) { return !(pivot < em); });
  } else {
    middle1 = std::partition(std::execution::par, first, last, [pivot](const auto &em) { return em < pivot; });
    middle2 = std::partition(std::execution::par, middle1, last, [pivot](const auto &em) { return !(pivot < em); });
  }
  quicksort(first, middle1);
  quicksort(middle2, last);
}
