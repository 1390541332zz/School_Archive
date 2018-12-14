#ifndef EXERCISE04_MYVECTOR_TPP
#define EXERCISE04_MYVECTOR_TPP

template<typename T>
MyVector<T>::MyVector() {}

template<typename T>
MyVector<T>::MyVector(MyVector const & rhs) 
    : sz(rhs.sz), alloc_sz(rhs.alloc_sz), arr(new T[alloc_sz])
{ 
    std::copy(rhs.arr.get(), (rhs.arr.get() + rhs.sz), arr.get());
}

template<typename T>
MyVector<T>::~MyVector() {}

template<typename T>
std::size_t MyVector<T>::size() const noexcept
{
    return sz;
}

template<typename T>
bool MyVector<T>::empty() const noexcept
{
    return (sz == 0);
}

template<typename T>
void MyVector<T>::push_back(T const & x)
{
    if (sz == alloc_sz) {
        alloc_sz *= 2;
        auto tmp = std::move(arr);
        arr.reset(new T[alloc_sz]);
        std::copy(tmp.get(), (tmp.get() + sz), arr.get());
    }
    arr[sz++] = x;
}

template<typename T>
T & MyVector<T>::at(std::size_t i)
{
    if (i >= sz) throw std::range_error("Out of Bounds");
    return arr[i];
}

template<typename T>
T const & MyVector<T>::at(std::size_t i) const
{
    if (i >= sz) throw std::range_error("Out of Bounds");
    return arr[i];
}

template<typename T>
MyVector<T> & MyVector<T>::operator=(MyVector<T> const & rhs)
{
    if (&rhs == this) return *this;
    sz = rhs.sz;
    alloc_sz = rhs.alloc_sz;
    arr.reset(new T[alloc_sz]);
    std::copy(rhs.arr.get(), (rhs.arr.get() + rhs.sz), arr.get());
    return *this;
}

#endif /* EXERCISE04_MYVECTOR_TPP */
