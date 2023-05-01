// From "The Standard Algorithms in C++" by Simon Toth
// See https://github.com/HappyCerberus/book-cpp-algorithms

#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <vector>

int main() {
  {
#include "for_each_code_range.h"
    assert(sum == 45);
  }
  {
#include "for_each_code_simple.h"
    assert(sum == 45);
  }
  {
#include "for_each_code_parallel.h"
  } {
#include "for_each_code_cpp20.h"
    assert(sum == 10);
  }
  std::cerr << ".";
}
