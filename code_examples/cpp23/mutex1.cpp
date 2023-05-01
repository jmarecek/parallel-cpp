#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
  using namespace std::chrono_literals;
  struct Shared {
    int value;
    std::mutex mux;
  };
  Shared shared{0, {}};
  auto t1 = std::jthread([&shared] {
    std::this_thread::sleep_for(1s);
    for (int i = 0; i < 10; i++) {
      std::this_thread::yield();
      {
        std::unique_lock lock(shared.mux);
        shared.value += 10;
      } // mutex unlocks!
      std::this_thread::sleep_for(1s);
    }
  });
}