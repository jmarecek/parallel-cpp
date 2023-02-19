#include <barrier>
#include <syncstream>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
​
int main() {
​
  auto on_completion = []() noexcept { 
    std::osyncstream(std::cout) << " hit! ";
  };
  std::barrier b(2, on_completion);

  std::vector<std::jthread> runners;

  auto work = [&]() {
    std::osyncstream(std::cout) << std::this_thread::get_id() << "/1" << std::endl;
    std::this_thread::yield();
    b.arrive_and_wait();
    std::osyncstream(std::cout) << std::this_thread::get_id() << "/2" << std::endl;
    std::this_thread::yield();
    b.arrive_and_wait();
  };
 
  for (int cnt=0; cnt < 2; cnt++) {
    threads.emplace_back(work);
  }​
}