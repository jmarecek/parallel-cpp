// https://en.cppreference.com/w/cpp/language/coroutines

#include <coroutine>
#include <iostream>
#include <syncstream>
 
struct promise;
 
struct coroutine : std::coroutine_handle<promise> {
    using promise_type = struct promise;
};
 
struct promise {
    coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
};
 
int main() {
    coroutine h = [](int i) -> coroutine {
        std::osyncstream(std::cout) << i;
        co_return;
    }(0);
    h.resume(); 
    h.destroy();
}