// based on https://en.cppreference.com/w/cpp/atomic/atomic/compare_exchange 
#include <atomic>
#include <stack>

template<typename T>
struct Node {
  T data;
  Node* next;
  Node(const T& data) : data(data), next(nullptr) {}
};

template<typename T> class stack {
    std::atomic<Node<T>*> head;
    public:
    void push(const T& data) {
        Node<T>* new_node = new Node<T>(data);
        new_node->next = head.load(std::memory_order_relaxed);
        while(!head.compare_exchange_weak(new_node->next, new_node, std::memory_order_release, std::memory_order_relaxed));
    }
};

int main() {
    std::stack<int> s; s.push(1); s.push(2); s.push(3);
}