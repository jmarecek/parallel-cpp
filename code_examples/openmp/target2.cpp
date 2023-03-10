// As per https://www.openmp.org/wp-content/uploads/2021-10-20-Webinar-OpenMP-Offload-Programming-Introduction.pdf, best compiled with:
// clang/LLVM: clang -fopenmp -fopenmp-targets=<target triple>
// GNU: gcc -fopenmp
// AMD ROCm: clang -fopenmp -offload-arch=gfx908
// NVIDIA: nvcc –mp=gpu -gpu=cc80
// Intel: icx -fiopenmp -fopenmp-targets=spir64
// IBM XL: xlc –qsmp –qoffload –qtgtarch=sm_70

#include <vector>
#include "omp.h"
#include "target2.h"

int main() {
  float a = 1.0;
  int sz = 1000;
  std::vector<float> vx(sz);
  float* x = vx.data();
  std::vector<float> vy(sz);
  float* y = vy.data();
  saxpy(a, x, y, sz);    
  return 0;
}