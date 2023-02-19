#include <coroutine>
#include <generator>
#include <iostream>
#include <syncstream>
 
std::generator<int> work() { 
    for (int i = 0; i < 10; i++) {
        co_yield i;
    }
}  

int main() { 
    for (int i : work()) { 
        std::osyncstream(std::cout) << ch << '\n'; 
    } 
} 