// Copyright EPCC, The University of Edinburgh, www.epcc.ed.ac.uk
// Creative Commons AttributionNonCommercial-ShareAlike 4.0 International License.

#pragma omp target teams distribute parallel for\
map(to:B,C), map(tofrom:sum) reduction(+:sum)
for (int i=0; i<N; i++){
  sum += B[i] + C[i];
}