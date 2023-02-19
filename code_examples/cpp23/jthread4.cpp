#include <iostream>
#include <syncstream>
#include <thread>
using namespace std::chrono_literals;

int main() {
    auto t1 = std::jthread([](std::stop_token token){
        while (!token.stop_requested()) {
            std::osyncstream(std::cout) << "A thread";
            std::this_thread::sleep_for(1s);
        }
        std::osyncstream(std::cout) << "Stop requested";
    });

    std::this_thread::sleep_for(2s);

    std::osyncstream(std::cout) << "Main thread";
    t1.request_stop();
}