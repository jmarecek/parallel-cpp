#include <algorithm>
#include <barrier>
#include <iostream>
#include <random>
#include <syncstream>
#include <thread>
#include <vector>

int main() {

  std::barrier b(4, [id = 1]() mutable noexcept {
    std::osyncstream(std::cout) << id << " OK" << std::endl;
    id++;
  });
  std::vector<std::jthread> runners;

  std::generate_n(std::back_inserter(runners), 4, [&b] {
    return std::jthread([&b] {
      std::osyncstream(std::cout) << std::this_thread::get_id() << "/1" << std::endl;
      std::this_thread::yield();
      b.arrive_and_wait();
      std::osyncstream(std::cout) << std::this_thread::get_id() << "/2" << std::endl;
      std::this_thread::yield();
      b.arrive_and_wait();
    });
  });
  runners.clear();
  std::osyncstream(std::cout) << std::endl;
}