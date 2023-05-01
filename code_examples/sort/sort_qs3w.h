
template <class RanIt, class _Pred>
void qsort3w(RanIt _First, RanIt _Last, _Pred compare) {
  if (_First >= _Last)
    return;

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
      } else
        _FwdIt++;
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
