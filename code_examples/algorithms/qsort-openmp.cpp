// the following code is based on Intel Develop article:
// https://software.intel.com/content/www/us/en/develop/articles/an-efficient-parallel-three-way-quicksort-using-intel-c-compiler-and-openmp-45-library.html

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <execution>
#include "tbb/task_scheduler_init.h"

using namespace std::chrono;

std::size_t g_depth = 0L;
const std::size_t cutoff = 1000000L;

template<class RanIt, class _Pred>
void qsort3w(RanIt _First, RanIt _Last, _Pred compare) {
    if (_First >= _Last) return;

    std::size_t _Size = 0L;
    g_depth++;
    if ((_Size = std::distance(_First, _Last)) > 0) {
        RanIt _LeftIt = _First, _RightIt = _Last;
        bool is_swapped_left = false, is_swapped_right = false;
        typename std::iterator_traits<RanIt>::value_type _Pivot = *_First;

        RanIt _FwdIt = _First + 1;
        while (_FwdIt <= _RightIt) {
            if (compare(*_FwdIt, _Pivot)) {
                is_swapped_left = true;
                std::iter_swap(_LeftIt, _FwdIt);
                _LeftIt++;
                _FwdIt++;
            } else if (compare(_Pivot, *_FwdIt)) {
                is_swapped_right = true;
                std::iter_swap(_RightIt, _FwdIt);
                _RightIt--;
            } else _FwdIt++;
        }

        if (_Size >= cutoff) {
#pragma omp taskgroup
            {
#pragma omp task untied mergeable
                if ((std::distance(_First, _LeftIt) > 0) && (is_swapped_left))
                    qsort3w(_First, _LeftIt - 1, compare);

#pragma omp task untied mergeable
                if ((std::distance(_RightIt, _Last) > 0) && (is_swapped_right))
                    qsort3w(_RightIt + 1, _Last, compare);
            }
        } else {
#pragma omp task untied mergeable
            {
                if ((std::distance(_First, _LeftIt) > 0) && is_swapped_left)
                    qsort3w(_First, _LeftIt - 1, compare);

                if ((std::distance(_RightIt, _Last) > 0) && is_swapped_right)
                    qsort3w(_RightIt + 1, _Last, compare);
            }
        }
    }
}

template<class BidirIt, class _Pred>
std::size_t sorted(BidirIt _First, BidirIt _Last, \
        std::size_t &position, _Pred compare) {
    bool is_sorted = true;

    BidirIt _MidIt = _First + (_Last - _First) / 2;
    if (compare(*_MidIt, *_First) || compare(*(_Last - 1), *_MidIt) ||
        compare(*(_Last - 1), *_First))
        return !is_sorted;

    for (auto _FwdIt = _First; _FwdIt != _Last - 1 && is_sorted; _FwdIt++) {
        if (compare(*(_FwdIt + 1), *_FwdIt)) {
            if (is_sorted == true)
                position = std::distance(_First, _FwdIt);

            is_sorted = false;
        }
    }

    return is_sorted;
}

template<class BidirIt, class _Pred>
void parallel_sort(BidirIt _First, BidirIt _Last, _Pred compare) {
    std::size_t pos = 0L;
    g_depth = 0L;
    if (!sorted(_First, _Last, pos, compare)) {
#pragma omp parallel num_threads(1)
#pragma omp master
        qsort3w(_First, _Last - 1, compare);
    }
}

int main() {
    tbb::task_scheduler_init init(4);
    const int N = 1000000;
    std::vector<int> v(N);
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(0, 255);
    std::generate(begin(v), end(v), [&]() { return dist(rng); });
    auto start = high_resolution_clock::now();
    parallel_sort(v.begin(), v.end(), std::less<int>());
    auto finish = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(finish - start);
    std::cout << "\nElapsed time = " << duration.count() << " ms\n";
    return 0;
}
