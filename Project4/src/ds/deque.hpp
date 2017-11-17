#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstdint>
#include <memory>
#include <iterator>
#include <algorithm>
#include <functional>
#include <exception>
#include "abstract_deque.hpp"


template <typename T>
class Deque : public AbstractDeque<T> {
private:
    struct node {
        std::unique_ptr<struct node> next = nullptr;
        struct node* prev = nullptr;
        T item = T();
    };

    std::unique_ptr<struct node> head = nullptr;
    struct node* tail = nullptr;
public:
    Deque();
    ~Deque();

    Deque(const Deque& rhs);
    Deque(Deque&& rhs);

    Deque& operator=(Deque&& rhs);
    Deque& operator=(const Deque& rhs);

    bool isEmpty() const noexcept;

    T front() const;
    T back() const;

    void pushFront(const T & item);
    void popFront();

    void pushBack(const T & item);
    void popBack();
};

#include "deque.tpp"

#endif /* DEQUE_HPP */
