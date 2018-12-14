#ifndef EXERCISE04_MYVECTOR_HPP
#define EXERCISE04_MYVECTOR_HPP

#include <memory>
#include <exception>

template<typename T>
class MyVector {
private:
    std::size_t sz = 0;
    std::size_t alloc_sz = 0;
    std::unique_ptr<T[]> arr = nullptr;
public:
    MyVector();
    MyVector(MyVector<T> const & rhs);
    ~MyVector();

    std::size_t size() const noexcept;
    bool empty() const noexcept;
    void push_back(T const & x);
    T & at(std::size_t i);
    T const & at(std::size_t i) const;

    MyVector<T> & operator=(MyVector<T> const & rhs);
};

#include "MyVector.tpp"

#endif /* EXERCISE04_MYVECTOR_HPP */
