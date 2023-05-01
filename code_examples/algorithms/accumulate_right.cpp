// From "The Standard Algorithms in C++" by Simon Toth
// See https://github.com/HappyCerberus/book-cpp-algorithms

#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

int main() {
#include "accumulate_right_code.h"
  assert(left_fold == 8);
  assert(right_fold == 3);

  std::cerr << ".";
}
