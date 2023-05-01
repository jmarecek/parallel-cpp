// From "The Standard Algorithms in C++" by Simon Toth
// See https://github.com/HappyCerberus/book-cpp-algorithms

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
#include "qsort_code.h"
  auto cmp = {-8, -1, 1, 2, 7, 9};
  assert(std::equal(&data[0], &data[size], cmp.begin()));
  std::cerr << ".";
}
