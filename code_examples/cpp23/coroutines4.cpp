// This code is based on the work of Simon Toth,
// https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

#include "coroutines4.h"
#include <coroutine>
#include <iostream>

Generator myCoroutine() {
  int x = 0;
  while (true) {
    co_yield x++;
  }
}

int main() {
  auto c = myCoroutine();
  int x = 0;
  while ((x = c.get_next()) < 10) {
    std::cout << x << "\n";
  }
}