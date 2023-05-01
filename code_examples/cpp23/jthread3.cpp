#include <iostream>
#include <syncstream>
#include <thread>
using namespace std::chrono_literals;

int main() {

  auto t1 = std::jthread([]() {
    std::osyncstream(std::cout) << "Another thread" << std::endl;
    std::this_thread::sleep_for(1s);
  });

  std::this_thread::sleep_for(2s);
  std::osyncstream(std::cout) << "Main thread" << std::endl;
}