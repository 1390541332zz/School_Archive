template<typename T>
MyVector<T>::MyVector() {}

template<typename T>
MyVector<T>::~MyVector() {}


template<typename T>
MyVector<T>::MyVector(MyVector const & other) : alloc_sz(other.alloc_sz), sz(other.sz)
{
    if (other.sz == 0) return;
    arr.reset(new T[alloc_sz]);
    std::copy(other.arr.get(), other.arr.get() + sz, arr.get());
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector const & rhs)
{
    if (&rhs == this) return *this;
    if (rhs.sz == 0) {
        arr.reset();
        sz = 0;
        alloc_sz = 0;
        return *this;
    }
    sz = rhs.sz;
    alloc_sz = rhs.alloc_sz;
    arr.reset(new T[alloc_sz]);
    std::copy(rhs.arr.get(), rhs.arr.get() + sz, arr.get());
    return *this;
}

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
void MyVector<T>::push_back(T const& item) noexcept 
{
    if (alloc_sz == 0) {
        arr.reset(new T[SCALE_FACTOR]);
        alloc_sz = SCALE_FACTOR;
    } else if (sz == alloc_sz) {
        std::unique_ptr<T[]> tmp(std::move(arr));
        alloc_sz *= SCALE_FACTOR;
        arr.reset(new T[alloc_sz]);
        std::move(tmp.get(), tmp.get() + sz, arr.get());
    }
    arr[sz] = item;
    ++sz;
}

template<typename T>
T& MyVector<T>::at(std::size_t i)
{
    if (i >= sz) throw std::range_error("Error: Index Out of Bounds"); 
    return arr[i];
}

template<typename T>
T const & MyVector<T>::at(std::size_t i) const
{
    if (i >= sz) throw std::range_error("Error: Index Out of Bounds");
    return arr[i];
}
