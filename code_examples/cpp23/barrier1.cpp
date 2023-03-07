#include <barrier>
#include <syncstream>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>

int main() {
    std::barrier b(5);
    std::vector<std::jthread> ts;
    std::generate_n(std::back_inserter(ts), 5, [&b]{
        return std::jthread([&b]{
            std::mt19937 gen(std::hash<std::thread::id>{}(std::this_thread::get_id()));
            std::bernoulli_distribution d(0.3);
            int cnt = 1;
            while (true) {
                std::osyncstream(std::cout) << std::this_thread::get_id() << "/" << cnt << std::endl;
                std::this_thread::yield();
                if (d(gen)) { 
                    b.arrive_and_drop();
                    return;
                } else {
                    b.arrive_and_wait();
                }
                cnt++;
            }
        });
    });
}