#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

void Foobar(int cnt);

int main(int argc, char* argv[]) {
    std::vector<std::jthread> threads;
    for (int cnt=0; cnt < 10; cnt++) {
        threads.push_back(std::jthread(Hello, cnt));
    }
    std::osyncstream(std::cout) << "Main thread" << std::endl;
    return 0;
}

void Foobar(int cnt) {
    std::osyncstream(std::cout) << "Thread " << cnt << std::endl;
}