#include <iostream>
#include <syncstream>
#include <mutex>
#include <condition_variable>
#include <thread>
using namespace std::chrono_literals;

struct Resource {
    std::mutex mux;
    bool ready = false;
};

int main() {
    Resource resource;
    auto t = std::jthread([&resource](std::stop_token token) {
        std::unique_lock lock(resource.mux);
        std::condition_variable_any().wait(lock, token, 
            [&resource] { return resource.ready; });
        if (resource.ready) {
            std::osyncstream(std::cout) << "Resource ready" << std::endl;
        } else {
            std::osyncstream(std::cout) << "Stop requested" << std::endl;
        }
    });
    std::osyncstream(std::cout) << "Main thread" << std::endl;
    t.request_stop();
    std::unique_lock lock(resource.mux);
    resource.ready = true;
    }
}