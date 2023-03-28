#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <vector>
using namespace std::chrono;

int main() {
  const int N = 1000000;
  std::vector<int> v(N);
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);
  std::generate(begin(v), end(v), [&]() { return dist(rng); });
  auto start = high_resolution_clock::now();
  std::sort(std::execution::par, begin(v), end(v));
  auto finish = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(finish - start);
  std::cout << "\nElapsed time = " << duration.count() << " ms\n";
  return 0;
}
