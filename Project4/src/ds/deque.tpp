#include "deque.hpp"

template <typename T>
Deque<T>::Deque() {}

template <typename T>
Deque<T>::~Deque() {}

template <typename T>
Deque<T>::Deque(const Deque& rhs)
{
    if(tail == rhs.tail) return;
    if (rhs.tail == nullptr) return;
    for (struct node* cur = rhs.tail; cur != nullptr; cur = cur->prev) {
        std::unique_ptr<struct node> tmp(new struct node);
        tmp->next = std::move(head);
        head = std::move(tmp);
        if (tail == nullptr) tail = head.get();
        if (head->next != nullptr) head->next->prev = head.get();
        head->item = cur->item;
    }
}

template <typename T>
Deque<T>::Deque(Deque&& rhs) : head(std::move(rhs.head)), tail(rhs.tail)
{
    rhs.tail = nullptr;
}

template <typename T>
Deque<T>& Deque<T>::operator=(Deque&& rhs)
{
    Deque tmp(rhs);
    head = std::move(tmp.head);
    tail = tmp.tail;
    return *this;
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque& rhs)
{
    if (tail == rhs.tail) return *this;
    Deque tmp(rhs);
    head = std::move(tmp.head);
    tail = tmp.tail;
    return *this;
}

template <typename T>
bool Deque<T>::isEmpty() const noexcept
{
    return (head == nullptr);
}

template <typename T>
T Deque<T>::front() const
{
    if (head == nullptr) throw std::runtime_error("Deque is Empty!");
    return head->item;
}

template <typename T>
T Deque<T>::back() const
{
    if (tail == nullptr) throw std::runtime_error("Deque is Empty!");
    return tail->item;
}

template <typename T>
void Deque<T>::pushFront(const T & item)
{
    std::unique_ptr<struct node> tmp(new struct node);
    if (head.get() != nullptr) head->prev = tmp.get();
    tmp->next = std::move(head);
    head = std::move(tmp);
    head->item = item;
    if (tail == nullptr) tail = head.get();
}

template <typename T>
void Deque<T>::popFront()
{
    if (head == nullptr) throw std::runtime_error("Deque is Empty!");
    if (tail == head.get()) tail = nullptr;
    head = std::move(head->next);
    if (head.get() != nullptr) head->prev = nullptr;
}

template <typename T>
void Deque<T>::pushBack(const T & item)
{
    if (head.get() == nullptr) {
        pushFront(item);
        return;
    }
    std::unique_ptr<struct node> tmp(new struct node);
    tmp->prev = tail;
    tail->next = std::move(tmp);
    tail = tail->next.get();
    tail->item = item;
}

template <typename T>
void Deque<T>::popBack()
{
    if (tail == nullptr) throw std::runtime_error("Deque is Empty!");
    if (tail == head.get()) {
        popFront();
        return;
    }
    tail = tail->prev;
    tail->next.reset();
}
