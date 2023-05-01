#include <iostream>
#include <thread>
#include <vector>

void Hello();

int main(int argc, char *argv[]) {
  std::vector<std::jthread> threads;
  for (int cnt = 0; cnt < 10; cnt++) {
    threads.push_back(std::jthread(Hello));
  }
  return 0;
}

void Hello() {
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
}