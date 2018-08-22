//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

template<typename T>
Stack<T>::Stack() : headPtr(nullptr), currentSize(0) {}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
bool Stack<T>::isEmpty() const {
	return (headPtr == nullptr);
}

template<typename T>
int Stack<T>::size() const {
	return currentSize;
}

template<typename T>
bool Stack<T>::push(const T& newItem) {
    Node<T>* tmp = nullptr;
    try {
        tmp = new Node<T>(newItem, headPtr);
    } catch (std::bad_alloc& ba_except) {
        return false;
    }
    headPtr = tmp;
    currentSize++;
	return true;
}

template<typename T>
T Stack<T>::peek() const throw(std::logic_error) {
    if (isEmpty()) throw std::logic_error("Attempted to access empty stack");
	return headPtr->getItem();
}

template<typename T>
bool Stack<T>::pop() {
    if (isEmpty()) return false;
    Node<T>* tmp = headPtr;
    headPtr = headPtr->getNext();
    delete tmp;
    currentSize--;
	return true;
}

template<typename T>
void Stack<T>::clear() {
    Node<T>* tmp = headPtr;
    while (headPtr != nullptr) {
        headPtr = headPtr->getNext();
        delete tmp;
        tmp = headPtr;
    }
    currentSize = 0;
}
