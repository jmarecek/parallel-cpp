// inspired by https://www.modernescpp.com/index.php/atomic-smart-pointers

#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

template <typename T>
class concurrent_stack {
  struct Node {
    T t;
    shared_ptr<Node> next;
  };
  atomic_shared_ptr<Node> head;
  concurrent_stack(concurrent_stack &) = delete;
  void operator=(concurrent_stack &) = delete;

public:
  concurrent_stack() = default;
  ~concurrent_stack() = default;
  class reference {
    shared_ptr<Node> p;

  public:
    reference(shared_ptr<Node> p_) : p{p_} {}
    T &operator*() { return p->t; }
    T *operator->() { return &p->t; }
  };

  auto find(T t) const {
    auto p = head.load();
    while (p && p->t != t)
      p = p->next;
    return reference(move(p));
  }
  auto front() const {
    return reference(head);
  }
  void push_front(T t) {
    auto p = make_shared<Node>();
    p->t = t;
    p->next = head;
    while (!head.compare_exchange_weak(p->next, p)) {
    }
  }
  void pop_front() {
    auto p = head.load();
    while (p && !head.compare_exchange_weak(p, p->next)) {
    }
  }
};