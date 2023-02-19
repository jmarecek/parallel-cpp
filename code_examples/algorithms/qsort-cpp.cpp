#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <execution>
#include "tbb/task_scheduler_init.h"

using namespace std::chrono;

// tbb::task_scheduler_init to set the number of threads

std::size_t threshold = 100;

template<class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) {
    if (first == last) return;
    std::size_t distance = std::distance(first, last);
    auto pivot = *std::next(first, distance / 2);
    ForwardIt middle1;
    ForwardIt middle2;
    if (distance < threshold) {
        middle1 = std::partition(std::execution::seq, first, last, [pivot](const auto &em) { return em < pivot; });
        middle2 = std::partition(std::execution::seq, middle1, last, [pivot](const auto &em) { return !(pivot < em); });
    } else {
        middle1 = std::partition(std::execution::par, first, last, [pivot](const auto &em) { return em < pivot; });
        middle2 = std::partition(std::execution::par, middle1, last, [pivot](const auto &em) { return !(pivot < em); });
    }
    quicksort(first, middle1);
    quicksort(middle2, last);
}

int main() {
    tbb::task_scheduler_init init(2);
    const int N = 1000000;
    std::vector<int> v(N);
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(0, 255);
    std::generate(begin(v), end(v), [&]() { return dist(rng); });
    auto start = high_resolution_clock::now();
    quicksort(v.begin(), v.end());
    auto finish = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(finish - start);
    std::cout << "\nElapsed time = " << duration.count() << " ms\n";
    return 0;
}
