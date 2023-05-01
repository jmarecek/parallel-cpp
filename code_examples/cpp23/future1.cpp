#include <chrono>
#include <future>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::chrono_literals;

void work(std::promise<void> barrier) {
  std::this_thread::sleep_for(1s);
  barrier.set_value();
}

int main() {
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::jthread t(work, std::move(barrier));
  barrier_future.wait();
}