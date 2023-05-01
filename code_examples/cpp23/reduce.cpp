#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

int main() {
#include "reduce_code.h"
  assert(sum == 15);
  assert(product == 120);

  std::cerr << ".";
}
