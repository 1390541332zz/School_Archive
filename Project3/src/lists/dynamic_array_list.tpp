#ifndef DYN_ARR_LIST_T
#define DYN_ARR_LIST_T

#include "dynamic_array_list.hpp"

static inline std::size_t round_base2(std::size_t x) {
    x--;
    for (std::size_t i = 1; i < sizeof(std::size_t)*8; i *= 2) {
        x |= x >> i;
    }
    if (x != SIZE_MAX) x++;
    return x;
}

template <typename T>
DynamicArrayList<T>::DynamicArrayList() {}

template <typename T>
DynamicArrayList<T>::~DynamicArrayList() {
    if (arr == nullptr) return;
    arr.reset();
    alloc_sz = 0;
    sz = 0;
}

template <typename T>
bool DynamicArrayList<T>::isEmpty() const noexcept {
    return (arr == nullptr);
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength() const noexcept {
    return sz;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t i, const T& item) {
    if (i > sz) throw std::range_error("Index Out of Bounds");
    if (i == sz) {
        push_back(item);
        return;
    }
    if (arr == nullptr) {
        alloc_sz = 2;
        arr = std::unique_ptr<T>(new T[alloc_sz]);
    } else if (sz == alloc_sz) {
        alloc_sz *= 2;
        std::unique_ptr<T> tmp(new T[alloc_sz]);
        arr.swap(tmp);
        if (i != 0) std::move(tmp.get(), tmp.get() + i - 1, arr.get());
        std::move(tmp.get() + i, tmp.get() + sz, arr.get() + i + 1);
    } else {
        std::move_backward(arr.get() + i, arr.get() + sz, arr.get() + i + 1);
    }
    arr[i] = item;
    sz++;
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t i) {
    if (i >= sz) throw std::range_error("Index Out of Bounds");
    if (i == sz) pop_back();
    arr[i] = T();
    sz--;
    std::move(arr.get() + i, arr.get() + sz, arr.get() + i + 1);
}

template <typename T>
void DynamicArrayList<T>::clear() noexcept {
    arr.reset();
    sz = 0;
    alloc_sz = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t i) const {
    if (i >= sz) throw std::range_error("Index Out of Bounds");
    return arr[i];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t i, const T& val) {
    if (i < 0 || i >= sz) throw std::range_error("Index Out of Bounds");
    arr[i] = val;
}

template <typename T>
void DynamicArrayList<T>::push_back(const T& item) {
    if (arr == nullptr) {
        alloc_sz = 2;
        arr = std::unique_ptr<T>(new T[alloc_sz]);
    } else if (sz == alloc_sz) {
        alloc_sz *= 2;
        std::unique_ptr<T> tmp(new T[alloc_sz]);
        arr.swap(tmp);
        std::move(tmp.get(), tmp.get() + sz, arr.get());
    }
    arr[sz] = item;
    sz++;
}

template <typename T>
void DynamicArrayList<T>::pop_back() noexcept   {
    sz--;
    arr[sz] = T();
}

#endif /* DYN_ARR_LIST_T */
