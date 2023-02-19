#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono_literals;

void A() {
    std::cout << "a";
    sleep_for(5s);
    std::cout << "A";
}

int main() {
    std::thread t(A);
    t.join();
}