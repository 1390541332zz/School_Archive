#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstdint>
#include <memory>
#include <iterator>
#include <algorithm>
#include <functional>
#include <exception>
#include "abstract_deque.hpp"
#include <deque>

template <typename T>
class Deque : public AbstractDeque<T> {
private:
    std::deque<T> d;
public:
    Deque() {}
    ~Deque() {}

    Deque(const Deque& rhs) {d = rhs.d;}
    Deque(Deque&& rhs) {d = std::move(rhs.d);}

    Deque& operator=(Deque&& rhs) {d = std::move(rhs.d); return *this;}
    Deque& operator=(const Deque& rhs) {d = rhs.d; return *this;}

    bool isEmpty() const noexcept {return d.empty();}

    bool for_each(const std::function<bool(const T&)>& fn) {return std::for_each(d.cbegin(), d.cend(), fn);}

    T front() const {return d.front();}
    T back() const {return d.back();}

    void pushFront(const T & item) {d.push_front(item);}
    void popFront() {d.pop_front();}

    void pushBack(const T & item) {d.push_back(item);}
    void popBack() {d.pop_back();}
};


#endif /* DEQUE_HPP */
