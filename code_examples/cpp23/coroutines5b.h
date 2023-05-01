// This code is based on the work of Simon Toth,
// https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d

bool Event::Awaiter::await_ready() const {
  // allow at most one waiter
  if (event.suspendedWaiter.load() != nullptr) {
    throw std::runtime_error("More than one awaiter is not valid");
  }

  return event.notified; // `false' suspends the coroutine
}

bool Event::Awaiter::await_suspend(std::coroutine_handle<> corHandle) noexcept {

  coroutineHandle = corHandle;

  if (event.notified)
    return false;

  // store the waiter for later notification
  event.suspendedWaiter.store(this);

  return true;
}

void Event::notify() noexcept {
  notified = true;

  // try to load the waiter
  auto *waiter = static_cast<Awaiter *>(suspendedWaiter.load());

  // check if a waiter is available
  if (waiter != nullptr) {
    // resume the coroutine => await_resume
    waiter->coroutineHandle.resume();
  }
}

Event::Awaiter Event::operator co_await() const noexcept {
  return Awaiter{*this};
}

Task receiver(Event &event) {
  auto start = std::chrono::high_resolution_clock::now();
  co_await event;
  std::cout << "Got the notification! " << std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Waited " << elapsed.count() << " seconds." << std::endl;
}