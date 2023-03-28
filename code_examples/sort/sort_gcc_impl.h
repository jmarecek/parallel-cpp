template <class _ExecutionPolicy, typename _RandomAccessIterator, typename _Compare, typename _LeafSort>
void
__parallel_stable_sort(_ExecutionPolicy&&, _RandomAccessIterator __xs, _RandomAccessIterator __xe, _Compare __comp,
                       _LeafSort __leaf_sort, std::size_t __nsort = 0)
{
    tbb::this_task_arena::isolate([=, &__nsort]() {
        //sorting based on task tree and parallel merge
        typedef typename std::iterator_traits<_RandomAccessIterator>::value_type _ValueType;
        typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type _DifferenceType;
        const _DifferenceType __n = __xe - __xs;
        if (__nsort == __n)
            __nsort = 0; // 'partial_sort' becames 'sort'

        const _DifferenceType __sort_cut_off = _PSTL_STABLE_SORT_CUT_OFF;
        if (__n > __sort_cut_off)
        {
            __buffer<_ValueType> __buf(__n);
            __root_task<__stable_sort_func<_RandomAccessIterator, _ValueType*, _Compare, _LeafSort>> __root{
                    __xs, __xe, __buf.get(), true, __comp, __leaf_sort, __nsort, __xs, __buf.get()};
            __task::spawn_root_and_wait(__root);
            return;
        }
        //serial sort
        __leaf_sort(__xs, __xe, __comp);
    });
} 

