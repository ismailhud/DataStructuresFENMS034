#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include "Node.h"
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include <utility>

template <typename T>
class XorLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    std::size_t size;

public:
    XorLinkedList();
    ~XorLinkedList();

    // Copy / move / initializer
    XorLinkedList(const XorLinkedList& other);
    XorLinkedList& operator=(const XorLinkedList& other);
    XorLinkedList(XorLinkedList&& other) noexcept;
    XorLinkedList& operator=(XorLinkedList&& other) noexcept;

    XorLinkedList(std::initializer_list<T> init);

    // Core ops
    void add_to_front(const T& value);
    void add_to_back(const T& value);
    void remove_from_front();
    void remove_from_back();

    // Accessors
    std::size_t count() const;
    T& get(std::size_t index);
    const T& get(std::size_t index) const;
    T& operator[](std::size_t index) { return get(index); }

    // Homework-required helper
    Node<T>* get_head() const { return head; }
    Node<T>* get_tail() const { return tail; }

    // Reverse the list (O(1) for XOR list: swap head/tail)
    void reverse();

    void clear();

    // Iterator implementation
    class Iterator {
        Node<T>* prev;
        Node<T>* curr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        Iterator(Node<T>* prevNode = nullptr, Node<T>* currNode = nullptr)
            : prev(prevNode), curr(currNode) {}

        reference operator*() const { return curr->data; }
        pointer operator->() const { return &(curr->data); }

        Iterator& operator++() {
            if (curr == nullptr) return *this;
            Node<T>* next = ptr_xor(prev, curr->both);
            prev = curr;
            curr = next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return curr != other.curr;
        }
    };

    Iterator begin() const { return Iterator(nullptr, head); }
    Iterator end() const { return Iterator(tail, nullptr); }
};

#include "XorLinkedList.tpp"

#endif // XOR_LINKED_LIST_H
