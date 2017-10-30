#ifndef DYN_ARR_LIST_H
#define DYN_ARR_LIST_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <algorithm>

#include "abstract_list.hpp"

template <typename T>
class DynamicArrayList : public AbstractList<T> {
private:
    std::unique_ptr<T[]> arr = nullptr;
    std::size_t alloc_sz = 0;
    std::size_t sz = 0;
public:
    DynamicArrayList();
    DynamicArrayList(const DynamicArrayList& rhs);

    ~DynamicArrayList();

    DynamicArrayList& operator=(const DynamicArrayList& rhs);

    bool isEmpty() const noexcept;
    std::size_t getLength() const noexcept;

    void insert(std::size_t i, const T& item);
    void remove(std::size_t i);

    void clear() noexcept;

    T getEntry(std::size_t i) const;
    void setEntry(std::size_t i, const T& val);
};

#include "dynamic_array_list.tpp"

#endif /* DYN_ARR_LIST_H */
