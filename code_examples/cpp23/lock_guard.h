#include <mutex>
#include <thread>
#include <iostream>
#include <syncstream>

std::mutex m1;
std::mutex m2;

void f(int id) {
    std::lock(m1, m2);
    std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);
    std::osyncstream(std::cout) << "Thread " << id << " says hi." << std::endl;
    //  we do not need to unlock  
}

int main(int argc, char* argv[]) {
    std::jthread t1(f, 1);
    std::jthread t2(f, 2);
}
