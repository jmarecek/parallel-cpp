#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> i(0);

int main() {
    auto t1 = std::jthread([](){
    	int j;
    	do { j = i.load(std::memory_order_relaxed); }
    	while (j == 0);
    	std::cout << j << std::endl;
    });
    auto t2 = std::jthread([](){
    	i.store(1, std::memory_order_relaxed);
    });
    return 0;
}