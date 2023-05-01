// based on memory4.cpp of "Introduction to SYCL",
// https://www.codingame.com/playgrounds/48226/introduction-to-sycl

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>

#include <CL/sycl.hpp>

class reduction_kernel;
namespace sycl = cl::sycl;

int main(int, char **) {
  std::array<int32_t, 16> arr;

  std::mt19937 mt_engine(std::random_device{}());
  std::uniform_int_distribution<int32_t> idist(0, 10);

  std::cout << "Data: ";
  for (auto &el : arr) {
    el = idist(mt_engine);
    std::cout << el << " ";
  }
  std::cout << std::endl;

  sycl::buffer<int32_t, 1> buf(arr.data(), sycl::range<1>(arr.size()));

  sycl::device device = sycl::default_selector{}.select_device();

  sycl::queue queue(device, [](sycl::exception_list el) {
    for (auto ex : el) {
      std::rethrow_exception(ex);
    }
  });

  size_t wgroup_size = 32;
  auto part_size = wgroup_size * 2;

  auto has_local_mem = device.is_host() || (device.get_info<sycl::info::device::local_mem_type>() != sycl::info::local_mem_type::none);
  auto local_mem_size = device.get_info<sycl::info::device::local_mem_size>();
  if (!has_local_mem || local_mem_size < (wgroup_size * sizeof(int32_t))) {
    throw "Device doesn't have enough local memory!";
  }

#include "buffer4.h"

  auto acc = buf.get_access<sycl::access::mode::read>();
  std::cout << "Sum: " << acc[0] << std::endl;

  return 0;
}
