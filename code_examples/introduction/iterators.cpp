#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main() {
#include "iterators_code.h"

  assert(it1 == data.begin());
  assert(std::distance(it1, it2) == 2);
  assert(std::distance(it1, it3) == 5);
  assert(it4 == data.end());
  std::cerr << ".";
}
