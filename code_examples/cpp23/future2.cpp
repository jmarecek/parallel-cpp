#include <iostream>
#include <syncstream>
#include <thread>
#include <future>

using namespace std::chrono_literals;
 
void work(std::promise<int> output_promise) {
    std::this_thread::sleep_for(2s);
    accumulate_promise.set_value(1);
}
 
int main() {
    std::promise<int> output_promise;
    std::future<int> output_future = output_promise.get_future();
    std::jthread t(std::move(accumulate_promise));
    std::osyncstream(std::cout) << output_future.get() << std::endl;
}