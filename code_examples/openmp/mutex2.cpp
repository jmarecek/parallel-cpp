#include <iostream>
#include <omp.h>

int count;
omp_nest_lock_t countMutex;

struct CountMutexInit {
    CountMutexInit() { omp_init_nest_lock   (&countMutex);   }
    ~CountMutexInit() { omp_destroy_nest_lock(&countMutex); }
} countMutexInit;

struct CountMutexHold {
    CountMutexHold() { omp_set_nest_lock    (&countMutex); }
    ~CountMutexHold() { omp_unset_nest_lock  (&countMutex); }
};

void Tick() {
    CountMutexHold releaseAtEndOfScope;
    count++;
}

int main() {
    Tick(); return 0;
}