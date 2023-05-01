// This code is based on the work of Simon Toth,
// https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

class Event {
public:
  Event() = default;

  Event(const Event &) = delete;
  Event(Event &&) = delete;
  Event &operator=(const Event &) = delete;
  Event &operator=(Event &&) = delete;

  class Awaiter;
  Awaiter operator co_await() const noexcept;

  void notify() noexcept;

private:
  friend class Awaiter;
  mutable std::atomic<void *> suspendedWaiter{nullptr};
  mutable std::atomic<bool> notified{false};
};

class Event::Awaiter {
public:
  Awaiter(const Event &eve) : event(eve) {}

  bool await_ready() const;
  bool await_suspend(std::coroutine_handle<> corHandle) noexcept;
  void await_resume() noexcept {}

private:
  friend class Event;

  const Event &event;
  std::coroutine_handle<> coroutineHandle;
};

struct Task {
  struct promise_type {
    Task get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};