#include "dynamic_array_list.hpp"

template <typename T>
bool DynamicArrayList::isEmpty() const noexcept {
    return (arr == nullptr);
}

template <typename T>
std::size_t DynamicArrayList::getLength() const noexcept {
    return sz;
}

template <typename T>
void DynamicArrayList::insert(std::size_t pos, const T& item) {
    if (pos < 0 || pos > sz) throw std::range_error("Index Out of Bounds");
    if (pos == sz) push_back(item);
    if (sz == alloc_sz) {
        alloc_sz += 2;
        std::unique_ptr<T> tmp(new T[alloc_sz]);
        if (pos != 0) std::memcpy(tmp.get(), arr.get(), pos);
        std::memcpy(tmp.get() + pos + 1, arr.get() + pos, sz - pos);
        arr.swap(tmp);
    } else {
        std::memmove(arr.get() + pos + 1, arr.get() + pos, sz - pos);
    }
    arr[pos] = item;
    sz++;
}

template <typename T>
void DynamicArrayList::remove(std::size_t pos) {
    if (pos < 0 || pos >= sz) throw std::range_error("Index Out of Bounds");
    if (pos == sz) pop_back();
    arr[pos] = T();
    std::memmove(arr.get() + pos, arr.get() + pos + 1, sz - pos - 1);
}

template <typename T>
void DynamicArrayList::clear() noexcept {
    arr.release();
    sz = 0;
    alloc_sz = 0;
}

template <typename T>
T DynamicArrayList::getEntry(std::size_t pos) const {
    if (pos < 0 || pos >= sz) throw std::range_error("Index Out of Bounds");
    return arr[pos];
}

template <typename T>
void DynamicArrayList::setEntry(std::size_t pos, const T& val) {
    if (pos < 0 || pos >= sz) throw std::range_error("Index Out of Bounds");
    arr[pos] = val;
}

template <typename T>
void DynamicArrayList::push_back(const T& item) {
    if (sz == alloc_sz) {
        alloc_sz += 2;
        std::unique_ptr<T> tmp(new T[alloc_sz]);
        std::memcpy(tmp.get(), arr.get(), sz);
        arr.swap(tmp);
    }
    arr[sz] = item;
    sz++;
}

template <typename T>
void DynamicArrayList::pop_back() {
    sz--;
    arr[sz] = T();
}
