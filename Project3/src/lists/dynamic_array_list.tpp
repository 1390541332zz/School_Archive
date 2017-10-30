#ifndef DYN_ARR_LIST_T
#define DYN_ARR_LIST_T

#include "dynamic_array_list.hpp"

template <typename T>
DynamicArrayList<T>::DynamicArrayList() {}

template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList& rhs)
                                    : alloc_sz(rhs.alloc_sz),
                                      sz(rhs.sz)
{
    if (rhs.isEmpty()) return;
    arr = std::unique_ptr<T[]>(new T[alloc_sz]);
    std::copy(rhs.arr.get(), rhs.arr.get() + sz, arr.get());
}

template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
    if (arr == nullptr) return;
    arr.reset();
    alloc_sz = 0;
    sz = 0;
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(const DynamicArrayList& rhs)
{
    if (arr != nullptr) clear();
    if (rhs.isEmpty()) return *this;
    alloc_sz = rhs.alloc_sz;
    sz = rhs.sz;
    arr = std::unique_ptr<T[]>(new T[alloc_sz]);
    std::copy(rhs.arr.get(), rhs.arr.get() + sz, arr.get());
    return *this;
}

template <typename T>
bool DynamicArrayList<T>::isEmpty() const noexcept
{
    return (sz == 0);
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength() const noexcept
{
    return sz;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t i, const T& item)
{
    if (i > sz) throw std::range_error("Index Out of Bounds");
    if (arr == nullptr) {
        alloc_sz = 2;
        arr = std::unique_ptr<T[]>(new T[alloc_sz]);
    } else if (sz == alloc_sz) {
        alloc_sz *= 2;
        std::unique_ptr<T[]> tmp(new T[alloc_sz]);
        arr.swap(tmp);
        if (i == sz) {
            std::move(tmp.get(), tmp.get() + sz, arr.get());
        } else {
            if (i != 0) std::move(tmp.get(), tmp.get() + i - 1, arr.get());
            std::move(tmp.get() + i, tmp.get() + sz, arr.get() + i + 1);
        }
    } else if (i < sz) {
        std::move(arr.get() + i, arr.get() + sz, arr.get() + i + 1);
    }
    arr[i] = item;
    sz++;
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t i)
{
    if (i >= sz) throw std::range_error("Index Out of Bounds");
    arr[i] = T();
    sz--;
    if(i == sz + 1) return;
    std::move_backward(arr.get() + i + 1, arr.get() + sz + 1, arr.get() + sz);
}

template <typename T>
void DynamicArrayList<T>::clear() noexcept
{
    arr.reset();
    sz = 0;
    alloc_sz = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t i) const
{
    if (i >= sz) throw std::range_error("Index Out of Bounds");
    return arr[i];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t i, const T& val)
{
    if (i >= sz) throw std::range_error("Index Out of Bounds");
    arr[i] = val;
}

#endif /* DYN_ARR_LIST_T */
