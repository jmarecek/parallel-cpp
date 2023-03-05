// Based on parallel.1.c in standard OpenMP Examples 5.1
// https://www.openmp.org/wp-content/uploads/openmp-examples-5.1.pdf

#include <omp.h>

void subdomain(float *x, int istart, int ipoints) {
    int i;
    for (i = 0; i < ipoints; i++) x[istart+i] = 123;
}

void sub(float *x, int npoints) {
    int iam, nt, ipoints, istart;

#pragma omp parallel default(shared) private(iam,nt,ipoints,istart)
    {
        iam = omp_get_thread_num();
        nt =  omp_get_num_threads();
        ipoints = npoints / nt;    /* size of partition */
        istart = iam * ipoints;  /* starting array index */
        if (iam == nt-1)     /* last thread may do more */
            ipoints = npoints - istart;
        subdomain(x, istart, ipoints);
    }
}

int main() {
    float array[10000];
    sub(array, 10000);
    return 0;
}