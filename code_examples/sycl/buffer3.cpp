#include <CL/sycl.hpp>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>

using namespace cl::sycl;
class buffer3;

int main(int, char **) {

  std::vector<float> a{2.0, 3.0, 7.0, 4.0};
  std::vector<float> b{4.0, 6.0, 1.0, 3.0};
  std::vector<float> c{0.0, 0.0, 0.0, 0.0};

  default_selector device_selector;

  queue q(device_selector);

  std::cout << "Running on "
            << q.get_device().get_info<info::device::name>()
            << "\n";
  {
    buffer bufA(a);
    buffer bufB(b);
    buffer bufC(c);

    q.submit([&](handler &cgh) {
      auto accA = accessor(bufA, cgh, read_only);
      auto accB = accessor(bufB, cgh, read_only);
      auto accC = accessor(bufC, cgh, write_only);
      cgh.parallel_for<class buffer3>(bufC.get_range(), [=](id<1> i) {
        accC[i] = accA[i] + accB[i];
      });
    });
    q.wait_and_throw();
  }

  return 0;
}
