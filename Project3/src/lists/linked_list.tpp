#ifndef LINKED_LIST_T
#define LINKED_LIST_T

#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() {}

template <typename T>
LinkedList<T>::~LinkedList() {}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept {
    return (head == nullptr);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept {
    return sz;
}

template <typename T>
void LinkedList<T>::insert(std::size_t pos, const T& item) {
    if (pos > sz) throw std::range_error("Index Out of Bounds");
    std::unique_ptr<struct node<T>> new_node(new struct node<T>);
    new_node->item = item;
    if (head == nullptr) {
        head.swap(new_node);
        sz++;
        return;
    }

    Node<T>* tmp = head.get();
    for (std::size_t i = 0; i < pos - 1; i++) {
        tmp = tmp->next.get();
    }
    new_node->next.swap(tmp->next);
    tmp->next = new_node;
    sz++;
}

template <typename T>
void LinkedList<T>::remove(std::size_t pos) {
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    std::unique_ptr<struct node<T>> node();
    if (pos == 0) {
        node = head;
        head = node->next;
        sz--;
        return;
    }
    Node<T>* tmp = head.get();
    for (std::size_t i = 0; i < pos - 1; i++) {
        tmp = tmp->next.get();
    }
    node = tmp->next;
    tmp->next = node->next;
    sz--;
}

template <typename T>
void LinkedList<T>::clear() noexcept {
    head.reset();
    sz = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t pos) const {
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    Node<T>* tmp = head.get();
    for (std::size_t i = 0; i < pos; i++) {
        tmp = tmp->next.get();
    }
    return tmp->item;
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t pos, const T& val) {
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    Node<T>* tmp = head.get();
    for (std::size_t i = 0; i < pos; i++) {
        tmp = tmp->next.get();
    }
    tmp->item = val;
}

template <typename T>
void LinkedList<T>::push_back(const T& val) {
    insert(sz, val);
}

template <typename T>
void LinkedList<T>::pop_back() noexcept {
    remove(sz - 1);
}

#endif /* LINKED_LIST_T */
