#ifndef NYVECTOR_H
#define MYVECTOR_H

#include <memory>
#include <stdexcept>

#define SCALE_FACTOR 2

template<typename T>
class MyVector {
  private:
    std::unique_ptr<T[]> arr = nullptr;
    std::size_t alloc_sz = 0;
    std::size_t sz = 0;
  public:
    MyVector();
    ~MyVector();

    MyVector(MyVector const & other);
    MyVector& operator=(MyVector const & rhs);

    std::size_t size() const noexcept;
    bool empty() const  noexcept;
    void push_back(T const& item) noexcept;
    T& at(std::size_t i);
    T const& at(std::size_t i) const;
};

#include "myvector.tpp"

#endif /* MYVECTOR_H */
