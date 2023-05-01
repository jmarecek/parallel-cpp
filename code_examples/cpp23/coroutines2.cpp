// inspired by https://www.incredibuild.com/blog/cpp-coroutines-lets-play-with-them

#include <coroutine>
#include <generator>
#include <iostream>
#include <memory>
#include <string>
#include <syncstream>

std::generator<char> split - by - value(std::string s) {
  for (char ch : ps) {
    co_yield ch;
  }
}

std::generator<char> split - by - uniqueptr(std::unique_ptr<std::string> ps) {
  for (char ch : *ps) {
    co_yield ch;
  }
}

int main() {
  for (char ch : split - by - value("test")) {
    std::osyncstream(std::cout) << ch << '\n';
  }
  for (char ch : split - by - uniqueptr(std::make_unique<std::string>("west"))) {
    std::osyncstream(std::cout) << ch << '\n';
  }
}