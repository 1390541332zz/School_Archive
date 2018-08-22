#ifndef LINKED_LIST_T
#define LINKED_LIST_T

#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& rhs) : sz(rhs.sz)
{
    if (rhs.isEmpty()) return;
    head = std::unique_ptr<struct node>(new struct node);
    head->item = rhs.head->item;
    struct node* tmp = head.get();
    struct node* rhs_tmp = rhs.head->next.get();
    for (std::size_t i = 1; i < sz; i++) {
        std::unique_ptr<struct node> new_node(new struct node);
        new_node->item = rhs_tmp->item;
        tmp->next = std::move(new_node);

        rhs_tmp = rhs_tmp->next.get();
        tmp = tmp->next.get();
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {}


template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& rhs)
{
    if (head == rhs.head) return *this;
    if (!isEmpty()) clear();
    if (rhs.isEmpty()) return *this;
    sz = rhs.sz;
    head = std::unique_ptr<struct node>(new struct node);
    head->item = rhs.head->item;
    struct node* tmp = head.get();
    struct node* rhs_tmp = rhs.head->next.get();
    for (std::size_t i = 1; i < sz; i++) {
        std::unique_ptr<struct node> new_node(new struct node);
        new_node->item = rhs_tmp->item;
        tmp->next = std::move(new_node);

        rhs_tmp = rhs_tmp->next.get();
        tmp = tmp->next.get();
    }
    return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
    return (head == nullptr);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
    return sz;
}

template <typename T>
void LinkedList<T>::insert(std::size_t pos, const T& item)
{
    if (pos > sz) throw std::range_error("Index Out of Bounds");
    std::unique_ptr<struct node> new_node(new struct node);
    new_node->item = item;
    if (pos == 0) {
        if (sz != 0) head.swap(new_node->next);
        head.swap(new_node);
        sz++;
        return;
    }
    struct node* tmp = head.get();

    for (std::size_t i = 0; i < pos - 1; i++) {
        tmp = tmp->next.get();
    }
    new_node->next = std::move(tmp->next);
    tmp->next = std::move(new_node);
    sz++;
}

template <typename T>
void LinkedList<T>::remove(std::size_t pos)
{
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    std::unique_ptr<struct node> node(nullptr);
    if (pos == 0) {
        node = std::move(head);
        head = std::move(node->next);
        sz--;
        return;
    }
    struct node* tmp = head.get();
    for (std::size_t i = 0; i < pos - 1; i++) {
        tmp = tmp->next.get();
    }
    node = std::move(tmp->next);
    tmp->next = std::move(node->next);
    sz--;
}

template <typename T>
void LinkedList<T>::clear() noexcept
{
    head.reset();
    sz = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t pos) const
{
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    struct node* tmp = head.get();
    for (std::size_t i = 0; i < pos; i++) {
        tmp = tmp->next.get();
    }
    return tmp->item;
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t pos, const T& val)
{
    if (pos >= sz) throw std::range_error("Index Out of Bounds");
    struct node* tmp = head.get();
    for (std::size_t i = 0; i < pos; i++) {
        tmp = tmp->next.get();
    }
    tmp->item = val;
}

#endif /* LINKED_LIST_T */
