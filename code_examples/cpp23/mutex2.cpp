#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;
    struct Shared {
        int value;
        std::mutex mux;
    };
    Shared shared{0,{}};
    auto t = std::jthread([&shared]{
        std::this_thread::sleep_for(1s);
        for (int i = 0; i < 10; i++) {
            {
               std::unique_lock lock(shared.mux);
               shared.value += 1;
            }
            std::this_thread::sleep_for(1s);
        }
    });
    auto observer = std::jthread([&shared]{
        while (true) {
            {
            std::unique_lock lock(shared.mux);
            std::cout << shared.value << std::endl;
            if (shared.value == 10)
                break;
            }
            std::this_thread::sleep_for(1s);
        }
    });
}