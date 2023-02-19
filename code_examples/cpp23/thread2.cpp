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

void B() {
    std::cout << "b";
    sleep_for(1s);
    std::cout << "B";
}

void C() {
    std::cout << "c";
    std::thread t(A);
    t.detach();
    std::thread u(B);
    u.join();
    std::cout << "C";
}

int main() {
    C();
    std::thread t(B);
    t.join();
    A();
}