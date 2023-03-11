// Based on https://github.com/NVIDIA/thrust/blob/main/examples/saxpy.cu

#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/functional.h>
#include <iostream>

struct saxpy_functor {
  const float a;
  saxpy_functor(float _a) : a(_a) {}
  __host__ __device__
  float operator()(const float& x, const float& y) const { 
    return a * x + y;
  }
};

int main(){
  thrust::device_vector<float> dx(1048576);
  thrust::fill(dx.begin(), dx.end(), 1.0);
  thrust::device_vector<float> dy(1048576);
  thrust::fill(dx.begin(), dx.end(), 2.0);
  // Y <- A * X + Y
  // thrust::transform(dx.begin(), dx.end(), dy.begin(), dy.begin(), 3.1415f * _1 + _2);
  thrust::transform(dx.begin(), dx.end(), dy.begin(), dy.begin(), saxpy_functor(3.1415));
  thrust::copy(dy.begin(), dy.end(), std::ostream_iterator<float>(std::cout, "\n"));
}