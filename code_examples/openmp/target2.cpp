#include "target2.h"
#include "omp.h"
#include <vector>

int main() {
  float a = 3.1415;
  int sz = 1048576;
  int num_blocks = 4096;
  std::vector<float> vx(sz);
  float *x = vx.data();
  std::vector<float> vy(sz);
  float *y = vy.data();
  saxpy(a, x, y, sz, num_blocks);
  return 0;
}