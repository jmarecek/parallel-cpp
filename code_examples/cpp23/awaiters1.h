// https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/std/coroutine#L313

  // 17.12.5 Trivial awaitables
  /// [coroutine.trivial.awaitables]
  struct suspend_always
  {
    constexpr bool await_ready() const noexcept { return false; }
    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    constexpr void await_resume() const noexcept {}
  };

  struct suspend_never
  {
    constexpr bool await_ready() const noexcept { return true; }
    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    constexpr void await_resume() const noexcept {}
  };