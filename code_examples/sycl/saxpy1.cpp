#include <iostream>
#include <cuda.h>
#define N 1048576

__global__ void saxpy_kernel(float a, float* x, float* y, float* z){
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) y[i] = a*x[i] + y[i];
}

int main(){
  std::vector<float> vx(N);
  float* x = vx.data();
  std::vector<float> vy(N);
  float* y = vy.data();
  std::vector<float> vz(N);
  float* z = vz.data();
  float *dx, *dy, *dz;
  cudaMalloc(&dx, N*sizeof(float));
  cudaMalloc(&dy, N*sizeof(float));
  cudaMalloc(&dz, N*sizeof(float));
  cudaMemcpy(dx, x, N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(dy, y, N*sizeof(float), cudaMemcpyHostToDevice);
  int nblocks = (n + 255) / 256;
  saxpy_kernel<<<nblocks, 256>>>(3.1415, dx, dy, dz);
  cudaMemcpy(z, dz, N*sizeof(float), cudaMemcpyDeviceToHost);
}