#ifndef XOR_LINKED_LIST_TPP
#define XOR_LINKED_LIST_TPP

#include "XorLinkedList.h"
#include <utility>

template <typename T>
XorLinkedList<T>::XorLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
XorLinkedList<T>::XorLinkedList(std::initializer_list<T> init)
    : head(nullptr), tail(nullptr), size(0) {
    for (const T& v : init) add_to_back(v);
}

template <typename T>
XorLinkedList<T>::~XorLinkedList() {
    clear();
}

template <typename T>
void XorLinkedList<T>::clear() {
    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    Node<T>* next;

    while (curr != nullptr) {
        next = ptr_xor(prev, curr->both);
        prev = curr;
        delete curr;
        curr = next;
    }

    head = tail = nullptr;
    size = 0;
}

template <typename T>
void XorLinkedList<T>::add_to_front(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->both = ptr_xor(nullptr, head);
        head->both = ptr_xor(newNode, ptr_xor(nullptr, head->both));
        head = newNode;
    }
    ++size;
}

template <typename T>
void XorLinkedList<T>::add_to_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (!tail) {
        head = tail = newNode;
    } else {
        newNode->both = ptr_xor(tail, nullptr);
        tail->both = ptr_xor(ptr_xor(tail->both, nullptr), newNode);
        tail = newNode;
    }
    ++size;
}

template <typename T>
void XorLinkedList<T>::remove_from_front() {
    if (!head) throw std::out_of_range("List is empty");

    Node<T>* temp = head;
    Node<T>* next = ptr_xor(nullptr, head->both);

    if (next) {
        next->both = ptr_xor(nullptr, ptr_xor(temp, next->both));
    } else {
        tail = nullptr;
    }

    head = next;
    delete temp;
    --size;
}

template <typename T>
void XorLinkedList<T>::remove_from_back() {
    if (!tail) throw std::out_of_range("List is empty");

    Node<T>* temp = tail;
    Node<T>* prev = ptr_xor(tail->both, nullptr);

    if (prev) {
        prev->both = ptr_xor(ptr_xor(prev->both, temp), nullptr);
    } else {
        head = nullptr;
    }

    tail = prev;
    delete temp;
    --size;
}

template <typename T>
std::size_t XorLinkedList<T>::count() const {
    return size;
}

template <typename T>
T& XorLinkedList<T>::get(std::size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");

    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    for (std::size_t i = 0; i < index; ++i) {
        next = ptr_xor(prev, curr->both);
        prev = curr;
        curr = next;
    }
    return curr->data;
}

template <typename T>
const T& XorLinkedList<T>::get(std::size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of range");

    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    for (std::size_t i = 0; i < index; ++i) {
        next = ptr_xor(prev, curr->both);
        prev = curr;
        curr = next;
    }
    return curr->data;
}

template <typename T>
XorLinkedList<T>::XorLinkedList(const XorLinkedList& other)
    : head(nullptr), tail(nullptr), size(0) {
    Node<T>* curr = other.head;
    Node<T>* prev = nullptr;
    Node<T>* next;

    while (curr != nullptr) {
        add_to_back(curr->data);
        next = ptr_xor(prev, curr->both);
        prev = curr;
        curr = next;
    }
}

template <typename T>
XorLinkedList<T>& XorLinkedList<T>::operator=(const XorLinkedList& other) {
    if (this == &other) return *this;
    clear();

    Node<T>* curr = other.head;
    Node<T>* prev = nullptr;
    Node<T>* next;

    while (curr != nullptr) {
        add_to_back(curr->data);
        next = ptr_xor(prev, curr->both);
        prev = curr;
        curr = next;
    }
    return *this;
}

template <typename T>
XorLinkedList<T>::XorLinkedList(XorLinkedList&& other) noexcept
    : head(other.head), tail(other.tail), size(other.size) {
    other.head = other.tail = nullptr;
    other.size = 0;
}

template <typename T>
XorLinkedList<T>& XorLinkedList<T>::operator=(XorLinkedList&& other) noexcept {
    if (this == &other) return *this;
    clear();

    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = other.tail = nullptr;
    other.size = 0;
    return *this;
}

template <typename T>
void XorLinkedList<T>::reverse() {
    // For XOR-linked list swapping head and tail reverses traversal order.
    std::swap(head, tail);
}

#endif // XOR_LINKED_LIST_TPP
