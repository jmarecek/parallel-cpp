// based on error_handling.cpp of "Introduction to SYCL",
// https://www.codingame.com/playgrounds/48226/introduction-to-sycl

#include <CL/sycl.hpp>
#include <iostream>

using namespace sycl;

class exception1;

int main(int, char **) {
  auto exception_handler = [](exception_list exceptions) {
    for (std::exception_ptr const &e : exceptions) {
      try {
        std::rethrow_exception(e);
      } catch (exception const &e) {
        std::cout << "Caught asynchronous SYCL exception:\n"
                  << e.what() << std::endl;
      }
    }
  };

  queue q(default_selector{}, exception_handler);
  // actual use of the q

  try {
    q.wait_and_throw();
  } catch (exception const &e) {
    std::cout << "Caught synchronous SYCL exception:\n"
              << e.what() << std::endl;
  }
  return 0;
}