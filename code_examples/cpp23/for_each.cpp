#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <vector>

int main() {
  {
#include "for_each_code_parallel.h"
  } {
#include "for_each_code_cpp20.h"
    assert(sum == 10);
  }
  std::cerr << ".";
}
