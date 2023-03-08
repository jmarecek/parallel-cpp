// This code is based on the work of Simon Toth, 
// https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

#include <coroutine>
#include <iostream>
#include "coroutines4.h"

Generator myCoroutine() {
    int x = 0;
    while (true) {
        co_yield x++;
    }
}

int main() {
    auto c = myCoroutine();
    int x = 0;
    while ((x = c.get_next()) < 10) {
        std::cout << x << "\n";
    }
}