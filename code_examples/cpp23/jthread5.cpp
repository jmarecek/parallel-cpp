#include <iostream>
#include <syncstream>
#include <atomic>
#include <thread>
using namespace std::chrono_literals;

int main() {

    auto t = std::jthread([](std::stop_token token) {
        std::osyncstream(std::cout) << "Thread " << std::this_thread::get_id() << std::endl;
        std::atomic<bool> flag = false;
        std::stop_callback callback(token, [&flag]{
            std::osyncstream(std::cout) << "Stop requested" << std::endl;
            flag = true;
        });
        while (!flag) {
            std::this_thread::sleep_for(1s);
        }
    });

    std::osyncstream(std::cout) << "Main thread" << std::endl;
    std::this_thread::sleep_for(3s);
    t.request_stop(); // runs all callbacks!
}