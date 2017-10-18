#ifndef DYN_ARR_LIST_H
#define DYN_ARR_LIST_H

#include <cstdlib>
#include <memory>

template <typename T>
class DynamicArrayList : public AbstractList{
private:
    std::unique_ptr<T> arr = nullptr;
    std::size_t sz = 0;
    std::size_t alloc_sz = 0;
public:
    bool isEmpty() const noexcept;

    std::size_t getLength() const noexcept;

    void push_back(const T& item);
    void pop_back(const T& item) noexcept;

    void insert(std::size_t pos, const T& item);
    void remove(std::size_t pos);

    void clear() noexcept;

    T getEntry(std::size_t pos) const;

    void setEntry(std::size_t pos, const T& val);


};


#include "dynamic_array_list.tpp"

#endif /* DYN_ARR_LIST_H */
