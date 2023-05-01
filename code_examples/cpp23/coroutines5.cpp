// This code is based on the work of Simon Toth,
// https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

#include <atomic>
#include <chrono>
#include <coroutine>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

#include "coroutines5a.h"
#include "coroutines5b.h"

using namespace std::chrono_literals;

int main() {

  std::cout << std::endl;

  std::cout << "Notification before waiting" << std::endl;
  Event event1{};
  auto senderThread1 = std::thread([&event1] { event1.notify(); });
  auto receiverThread1 = std::thread(receiver, std::ref(event1));

  receiverThread1.join();
  senderThread1.join();

  std::cout << std::endl;

  std::cout << "Notification after 2 seconds waiting" << std::endl;
  Event event2{};
  auto receiverThread2 = std::thread(receiver, std::ref(event2));
  auto senderThread2 = std::thread([&event2] {
    std::this_thread::sleep_for(2s);
    event2.notify();
  });

  receiverThread2.join();
  senderThread2.join();

  std::cout << std::endl;
}