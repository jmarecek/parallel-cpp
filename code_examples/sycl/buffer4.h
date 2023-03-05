// based on memory4.cpp of "Introduction to SYCL",
// https://www.codingame.com/playgrounds/48226/introduction-to-sycl
  
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
