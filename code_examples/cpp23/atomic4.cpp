#include "atomic4.h"
#include <atomic>
#include <iostream>
#include <queue>
#include <thread>

int main() {
  std::queue<int> numbers;
  SpinLock numbers_lock;
  int n = 0;
  for (n = 0; n < 10; ++n) {
    numbers.push(n);
  }
  for (n = 0; n < 2; n++) {
    std::jthread t{[n, &numbers, &numbers_lock]() {
      numbers_lock.lock();
      int val = numbers.front();
      numbers.pop();
      numbers_lock.unlock();
    }};
  }
}