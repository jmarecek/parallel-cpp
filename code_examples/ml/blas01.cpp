#include "mkldnn.hpp"
#include <iostream>
#include <vector>

using namespace mkldnn;
using dim_t = mkldnn::memory::dim;

int main(int argc, char **argv) {
  try {
    const dim_t n = 64;
    // column-major order (sloupce souvisle)
    std::vector<float> A(n * n, 1.0f);
    std::vector<float> B(n * n, 1.0f);
    std::vector<float> C(n * n, 1.0f);
    // https://oneapi-src.github.io/oneDNN/v0/group__c__api__blas.html
    mkldnn_status_t status = mkldnn_sgemm('N', 'N', n, n, n,
                                          1.f, A.data(), n, B.data(), n,
                                          0.f, C.data(), n);
    std::cerr << "status: " << status << std::endl;
  } catch (error &e) {
    std::cerr << "status: " << e.status << std::endl;
    std::cerr << "message: " << e.message << std::endl;
  }
  return 0;
}
