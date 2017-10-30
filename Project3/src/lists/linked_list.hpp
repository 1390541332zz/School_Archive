#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <algorithm>

#include "abstract_list.hpp"

template <typename T>
struct node {
    std::unique_ptr<node<T>> next = nullptr;
    T item = T();
};

template <typename T>
class LinkedList : public AbstractList<T> {
private:
    std::unique_ptr<struct node<T>> head = nullptr;
    std::size_t sz = 0;
public:
    LinkedList();
    LinkedList(const LinkedList& rhs);

    ~LinkedList();

    LinkedList& operator=(const LinkedList& rhs);

    bool isEmpty() const noexcept;
    std::size_t getLength() const noexcept;

    void insert(std::size_t pos, const T& item);
    void remove(std::size_t pos);

    void clear() noexcept;

    T getEntry(std::size_t pos) const;
    void setEntry(std::size_t pos, const T& val);
};

#include "linked_list.tpp"

#endif /* LINKED_LIST_H */
