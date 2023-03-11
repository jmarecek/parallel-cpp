#include <omp.h>

int count;
omp_nest_lock_t countMutex;

struct RAIIMutexInit {
    RAIIMutexInit() { omp_init_nest_lock   (&countMutex);   }
    ~RAIIMutexInit() { omp_destroy_nest_lock(&countMutex); }
} countMutexInit; // notice the scope!

struct RAIIMutexHold {
    RAIIMutexHold() { omp_set_nest_lock    (&countMutex); }
    ~ RAIIMutexHold() { omp_unset_nest_lock  (&countMutex); }
};

void work() {
  CountMutexHold releaseAtEndOfScope;
  count++;
}

int main() {
  work();
  return 0;
}