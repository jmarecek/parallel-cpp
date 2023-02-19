#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> i(0);

int main() {
    auto t1 = std::jthread([](){
    	int j;
    	do { j = i; }
    	while (j == 0);
    	std::cout << j << std::endl;
    });
    auto t2 = std::jthread([](){
    	i = 1;
    });
    return 0;
}