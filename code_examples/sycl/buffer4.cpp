// based on memory4.cpp of "Introduction to SYCL",
// https://www.codingame.com/playgrounds/48226/introduction-to-sycl

  #include <array>
  #include <cstdint>
  #include <iostream>
  #include <random>
  #include <cassert>

  #include <CL/sycl.hpp>
  
  class reduction_kernel;
  namespace sycl = cl::sycl;

  int main(int, char**) {
    std::array<int32_t, 16> arr;

    std::mt19937 mt_engine(std::random_device{}());
    std::uniform_int_distribution<int32_t> idist(0, 10);

    std::cout << "Data: ";
    for (auto& el : arr) {
      el = idist(mt_engine);
      std::cout << el << " ";
    }
    std::cout << std::endl;

    sycl::buffer<int32_t, 1> buf(arr.data(), sycl::range<1>(arr.size()));

    sycl::device device = sycl::default_selector{}.select_device();
    
    sycl::queue queue(device, [] (sycl::exception_list el) {
       for (auto ex : el) { std::rethrow_exception(ex); }
    } );

    // <<Set up queue and check device information>>
    /* Here we manually set the Work Group size to 32, 
    but there may be a more optimal size for your device */
    size_t wgroup_size = 32;
    
    auto part_size = wgroup_size * 2;

    auto has_local_mem = device.is_host()
        || (device.get_info<sycl::info::device::local_mem_type>()
        != sycl::info::local_mem_type::none);
    auto local_mem_size = device.get_info<sycl::info::device::local_mem_size>();
    if (!has_local_mem
      || local_mem_size < (wgroup_size * sizeof(int32_t)))
    {
       throw "Device doesn't have enough local memory!";
    }
  
    // <<Reduction loop>>
    auto len = arr.size();
    while (len != 1) {
       // division rounding up
       auto n_wgroups = (len + part_size - 1) / part_size;
       queue.submit([&] (sycl::handler& cgh) {
          sycl::accessor <int32_t, 1, sycl::access::mode::read_write, sycl::access::target::local>
                         local_mem(sycl::range<1>(wgroup_size), cgh);

          auto global_mem = buf.get_access<sycl::access::mode::read_write>(cgh);
          cgh.parallel_for<class reduction_kernel>(
               sycl::nd_range<1>(n_wgroups * wgroup_size, wgroup_size),
               [=] (sycl::nd_item<1> item) {
             
            size_t local_id = item.get_local_linear_id();
            size_t global_id = item.get_global_linear_id();
            local_mem[local_id] = 0;

            if ((2 * global_id) < len) {
               local_mem[local_id] = global_mem[2 * global_id] + global_mem[2 * global_id + 1];
            }
            item.barrier(sycl::access::fence_space::local_space);

            for (size_t stride = 1; stride < wgroup_size; stride *= 2) {
               auto idx = 2 * stride * local_id;
               if (idx < wgroup_size) {
                  local_mem[idx] = local_mem[idx] + local_mem[idx + stride];
               }

               item.barrier(sycl::access::fence_space::local_space);
            }

            if (local_id == 0) {
               global_mem[item.get_group_linear_id()] = local_mem[0];
            }
          });
       });
    queue.wait_and_throw();

    len = n_wgroups;
  }

    auto acc = buf.get_access<sycl::access::mode::read>();
    std::cout << "Sum: " << acc[0] << std::endl;

    return 0;
  }
