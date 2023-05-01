#include "omp.h"

int work() { return 0; }

int main() {
  int sum = 0;
#pragma omp parallel for reduction(+ \
                                   : sum)
  for (int i = 0; i < 42; i++)
    sum += work();
}