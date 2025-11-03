#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <cstddef>

template <typename T>
struct Node {
    T data;
    Node<T>* both; // XOR of prev and next

    explicit Node(const T& value) : data(value), both(nullptr) {}
};

// Base ptr_xor template
template <typename T>
inline Node<T>* ptr_xor(Node<T>* a, Node<T>* b) {
    return reinterpret_cast<Node<T>*>(
        reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)
    );
}

// Overloads to make nullptr usage convenient
template <typename T>
inline Node<T>* ptr_xor(std::nullptr_t, Node<T>* b) { return b; }

template <typename T>
inline Node<T>* ptr_xor(Node<T>* a, std::nullptr_t) { return a; }

#endif // NODE_H
