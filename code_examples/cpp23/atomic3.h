// based on https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/std/atomic

  template<typename _Tp>
    struct atomic
    {
      using value_type = _Tp;

[...]

      bool
      compare_exchange_strong(_Tp& __e, _Tp __i, memory_order __s,
			      memory_order __f) noexcept
      {
	return __atomic_impl::__compare_exchange(_M_i, __e, __i, false,
						 __s, __f);
      }

      bool
      compare_exchange_weak(_Tp& __e, _Tp __i, memory_order __s,
			    memory_order __f) noexcept
      {
	return __atomic_impl::__compare_exchange(_M_i, __e, __i, true,
						 __s, __f);
      }

[...]
    };



  /// Partial specialization for pointer types.
  template<typename _Tp>
    struct atomic<_Tp*>
    {
      using value_type = _Tp*;
      using difference_type = ptrdiff_t;

[...]

     bool
      compare_exchange_strong(__pointer_type& __p1, __pointer_type __p2,
			      memory_order __m1, memory_order __m2) noexcept
      { return _M_b.compare_exchange_strong(__p1, __p2, __m1, __m2); }

[...]

    };