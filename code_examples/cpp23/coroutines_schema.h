{
  co_await promise.initial_suspend();
  try {
    ...
  } catch (...) {
    promise.unhandled_exception();
  }
  // finally
  co_await promise.final_suspend();
}