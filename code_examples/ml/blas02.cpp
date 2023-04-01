#include <boost/numeric/ublas/tensor.hpp> 
#include <iostream>

int main()
{
  using namespace boost::numeric::ublas::index;
  using tensor  = boost::numeric::ublas::tensor_dynamic<float>;
  auto ones     = boost::numeric::ublas::ones<float>{};

  tensor A = ones(64,64);
  tensor B = ones(64,64);

  tensor C = A(_i,_j)*B(_i,_j); 
  std::cout << "C=" << C << ";" << std::endl;
}