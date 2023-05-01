#include <CL/sycl.hpp>
#include <cassert>
#include <iostream>

using namespace sycl;
class buffer1;

int main(int, char **) {

  default_selector device_selector;
  queue q(device_selector);

  {
#include "buffer1.h"
  }

  return 0;
}
