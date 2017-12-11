#include <iostream>
#include "MinPriorityQueue.hpp"

template<typename KeyT, typename T>
typename MinPriorityQueue<KeyT, T>::node* MinPriorityQueue<KeyT, T>::node::sibling() const
{
    if (parent == nullptr) throw std::logic_error("Node has no parent!");
    return ((parent->lhs.get() == this) ? rhs.get() : lhs.get());
}

template<typename KeyT, typename T>
void MinPriorityQueue<KeyT, T>::node::swap(node& rhs)
{
    if (this == &rhs) return;
    std::swap(key, rhs.key);
    std::swap(item, rhs.item);
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::node::operator<(const node& rhs) const noexcept
{
    return (key < rhs.key);
}

template<typename KeyT, typename T>
void MinPriorityQueue<KeyT, T>::update_heights(node* cur) noexcept
{
    while (cur != nullptr) {
        std::size_t max_ht = 0;
        cur->sz = 1;
        if (cur->lhs != nullptr && cur->rhs != nullptr) {
            if (cur->lhs->ht < cur->rhs->ht) {
                max_ht = cur->rhs->ht;
            } else {
                max_ht = cur->lhs->ht;
            }
            cur->sz += cur->lhs->sz + cur->rhs->sz;
        } else if (cur->lhs != nullptr) {
            max_ht = cur->lhs->ht;
            cur->sz += cur->lhs->sz;
        } else if (cur->rhs != nullptr) {
            max_ht = cur->rhs->ht;
            cur->sz += cur->rhs->sz;
        }
        cur->ht = max_ht + 1;
        cur = cur->parent;
    }
}

template<typename KeyT, typename T>
std::size_t MinPriorityQueue<KeyT, T>::optimal_height(std::size_t sz) const noexcept
{
	std::size_t ht = 0;
	while (sz > 0) {
		sz >>= 1;
		ht++;
	}
	return ht;
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::balance(node* cur)
{
    if (cur == nullptr) return true;
    if (cur->lhs == nullptr && cur->rhs == nullptr && cur->parent != nullptr) {
        KeyT key = cur->key;
        T item = cur->item;
        node* parent = cur->parent;
        if (parent->lhs != nullptr && parent->lhs.get() == cur) {
            parent->lhs.reset();
        } else {
            parent->rhs.reset();
        }
        update_heights(parent);
        insert(key, item);
        return true;
    }
    if (cur->lhs != nullptr && cur->lhs->ht > optimal_height(cur->lhs->sz)) {
        balance(cur->lhs.get());
    }
    if (cur->rhs != nullptr && cur->rhs->ht > optimal_height(cur->rhs->sz)) {
        balance(cur->rhs.get());
    }
	return true;
}

template<typename KeyT, typename T>
MinPriorityQueue<KeyT, T>::MinPriorityQueue() {}

template<typename KeyT, typename T>
MinPriorityQueue<KeyT, T>::~MinPriorityQueue() {}

template<typename KeyT, typename T>
int MinPriorityQueue<KeyT, T>::size() const
{
    return (head != nullptr) ? head->sz : 0;
}

template<typename KeyT, typename T>
int MinPriorityQueue<KeyT, T>::height() const
{
    return (head != nullptr) ? head->ht : 0;
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::isEmpty() const
{
    return (head == nullptr);
}

template<typename KeyT, typename T>
KeyT MinPriorityQueue<KeyT, T>::getMinValue() const throw(std::logic_error)
{
    if (isEmpty()) throw std::logic_error("Heap is Empty!");
    return head->key;
}

template<typename KeyT, typename T>
T MinPriorityQueue<KeyT, T>::getMinItem() const throw(std::logic_error)
{
    if (isEmpty()) throw std::logic_error("Heap is Empty!");
    return head->item;
}

template<typename KeyT, typename T>
void MinPriorityQueue<KeyT, T>::clear()
{
    head.reset();
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::insert(const KeyT& key, const T& item)
{
    std::unique_ptr<node> tmp(new node);
    tmp->key  = key;
    tmp->item = item;

    if (isEmpty()) {
        ++tmp->ht;
        head = std::move(tmp);
        return true;
    }

    node* cur = head.get();
    while (true) {
        if (cur->lhs != nullptr && cur->rhs != nullptr) {
            if (cur->lhs->ht < cur->rhs->ht) {
                cur = cur->lhs.get();
            } else {
                cur = cur->rhs.get();
            }
        } else {
            break;
        }
    }

    tmp->parent = cur;
    if (cur->lhs == nullptr) {
        cur->lhs = std::move(tmp);
        cur = cur->lhs.get();
    } else {
        cur->rhs = std::move(tmp);
        cur = cur->rhs.get();
    }
    update_heights(cur);

    while (cur->parent != nullptr && cur->key < cur->parent->key) {
        cur->swap(*(cur->parent));
        cur = cur->parent;
    }
    return true;
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::deleteMin() throw(std::logic_error)
{
    if (isEmpty()) throw std::logic_error("Heap is Empty!");
    if (head->sz == 1) {
        head.reset();
        return true;
    }
    node* cur = head.get();
    while (true) {
        node* child = nullptr;
        if (cur->lhs != nullptr && cur->rhs != nullptr) {
            if (cur->lhs->ht < cur->rhs->ht) {
                child = cur->lhs.get();
            } else {
                child = cur->rhs.get();
            }
        } else if (cur->lhs != nullptr) {
            child = cur->lhs.get();
        } else if (cur->rhs != nullptr) {
            child = cur->rhs.get();
        } else {
            break;
        }
        cur->swap(*child);
        cur = child;
    }
    node* parent = cur->parent;
    if (parent->lhs.get() == cur) {
        parent->lhs.reset();
    } else {
        parent->rhs.reset();
    }

    update_heights(parent);
    if (auto_rebalance) {
        auto_rebalance = false;
        balance(head.get());
        auto_rebalance = true;
    }
    return true;
}

template<typename KeyT, typename T>
void MinPriorityQueue<KeyT, T>::setAutoRebalance(bool val)
{
    auto_rebalance = val;
}

template<typename KeyT, typename T>
bool MinPriorityQueue<KeyT, T>::rebalance(int maxHeight)
{
    if (maxHeight < optimal_height(size())) return false;
    if (height() > maxHeight) {
        return balance(head.get());
    }
    return true;
}

template<typename KeyT, typename T>
void MinPriorityQueue<KeyT, T>::printTree()
{
    if (isEmpty()) return;
    std::vector<std::stringstream> v(height() + 1);
    std::function<void(node*,std::size_t)> f = [&] (node* cur, std::size_t i) {
        if (cur == nullptr) {
            v[i] << std::setw(3) << "|";
            return;
        }
        v[i] << std::setw(3) << cur->key;
        f(cur->lhs.get(), i + 1);
        f(cur->rhs.get(), i + 1);
    };
    f(head.get(), 0);
    for (auto& s : v) {
        std::cout << s.str() << std::endl;
    }
    std::cout << std::endl;
}
