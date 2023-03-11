// Based on https://github.com/jeffhammond/dpcpp-tutorial

#include <iostream>
#include "CL/sycl.hpp"

class saxpy3;

int main(int argc, char * argv[]) {
  std::vector<float> vx(1048576, 1.0);
  std::vector<float> vy(1048576, 2.0l);
  std::vector<float> vz(1048576, 0.0);
  sycl::queue q(sycl::default_selector{});
  try {
    const float A(aval);
    sycl::buffer<float,1> dx { vx.data(), sycl::range<1>(vx.size()) };
    sycl::buffer<float,1> dy { vy.data(), sycl::range<1>(vy.size()) };
    sycl::buffer<float,1> dz { vz.data(), sycl::range<1>(vz.size()) };

    q.submit([&](sycl::handler& h) {
      sycl::accessor x(dx, h, sycl::read_only);
      sycl::accessor y(dy, h, sycl::read_only);
      sycl::accessor z(dz, h, sycl::read_write);
      h.parallel_for<class saxpy3>( sycl::range<1>{length}, [=] (sycl::id<1> it) {
        const size_t i = it[0];
        z[I] += 3.1415 * x[i] + y[I];
      });
    });
    q.wait();
  }
  catch (sycl::exception & e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}