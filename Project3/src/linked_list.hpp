#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include

template <typename T>
class LinkedList : public AbstractList{
private:
    T* head = nullptr;
    std::size_t sz = 0;
public:
    bool isEmpty() const noexcept;

    std::size_t getLength() const noexcept;

    void insert(std::size_t pos, const T& item);

    void remove(std::size_t pos);

    void clear() noexcept;

    T getEntry(std::size_t pos) const;

    void setEntry(std::size_t pos, const T& val);
};


#include "dynamic_array_list.tpp"

#endif /* LINKED_LIST_H */
