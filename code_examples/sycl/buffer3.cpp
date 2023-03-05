// based on vector_add.cpp of standard documentation

#include <iostream>
#include <CL/sycl.hpp>

using namespace sycl;
class buffer3;

int main(int, char**) {

   float4 vec_a = { 2.0, 3.0, 7.0, 4.0 };
   float4 vec_b = { 4.0, 6.0, 1.0, 3.0 };
   float4 vec_c = { 0.0, 0.0, 0.0, 0.0 };

   default_selector device_selector;

   queue queue(device_selector);

   std::cout << "Running on "
             << queue.get_device().get_info<info::device::name>()
             << "\n";
   {
      buffer<float4, 1> vec_a_sycl(&vec_a, range<1>(1));
      buffer<float4, 1> vec_b_sycl(&vec_b, range<1>(1));
      buffer<float4, 1> vec_c_sycl(&vec_c, range<1>(1));

      queue.submit([&] (cl::sycl::handler& cgh) {

         auto vec_a_acc = vec_a_sycl.get_access<access::mode::read>(cgh);
         auto vec_b_acc = vec_b_sycl.get_access<access::mode::read>(cgh);
         auto vec_c_acc = vec_c_sycl.get_access<access::mode::discard_write>(cgh);

         cgh.single_task<class buffer3>([=] () {
         vec_c_acc[0] = vec_a_acc[0] + vec_b_acc[0];
         });
      });
   }

   return 0;
} 
