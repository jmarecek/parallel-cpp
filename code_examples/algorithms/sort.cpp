// From "The Standard Algorithms in C++" by Simon Toth
// See https://github.com/HappyCerberus/book-cpp-algorithms

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <list>
#include <vector>

int main() {
#include "sort_code.h"
  auto cmp = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  assert(std::ranges::equal(data1, cmp));
  assert(std::ranges::equal(data2, cmp));

  std::cerr << ".";
}
