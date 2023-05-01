#include <CL/sycl.hpp>
#include <cassert>
#include <iostream>

using namespace sycl;
class buffer2;

int main(int, char **) {

  default_selector device_selector;
  queue q(device_selector);

  {
#include "buffer2.h"
  } q.wait();

  return 0;
}
