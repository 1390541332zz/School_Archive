#ifndef LAMBDA_VECTOR_H
#define LAMBDA_VECTOR_H

#include <vector>
#include <mutex>

// Concept courtesy of Herb Sutter's talk
// C++ and Beyond 2012: Herb Sutter - C++ Concurrency
template<typename T>
class Vector {
private:
    mutable std::vector<T> v;
    mutable std::mutex m;
public:
    Vector() {}
    Vector(std::vector<T> vec) : v(vec) {}
    template <typename F>
    auto operator()(F fun) -> decltype(fun(v))
    {
        std::lock_guard<std::mutex> lock(m);
        return fun(v);
    }
};

#endif /* LAMBDA_VECTOR_H */
