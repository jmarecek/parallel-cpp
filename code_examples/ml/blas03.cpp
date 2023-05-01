#include <boost/numeric/ublas/tensor.hpp>
#include <iostream>

int main() {
  using namespace boost::numeric::ublas::index;
  using tensor = boost::numeric::ublas::tensor_dynamic<float>;
  auto ones = boost::numeric::ublas::ones<float>{};

  tensor A = ones(3, 4, 5);
  tensor B = ones(4, 6, 3, 2);

  tensor C = 2 * ones(5, 6, 2) + A(_i, _j, _k) * B(_j, _l, _i, _m) + 5;
  std::cout << "C=" << C << ";" << std::endl;
}