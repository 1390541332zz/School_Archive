//  Adapted from Frank M. Carrano and Timothy M. Henry.

/** @file Node.hpp  */
#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
class Node {
private:
	T        item; // A data item
	Node<T>* next; // Pointer to next node

public:
	Node();
	Node(const T& anItem);
	Node(const T& anItem, Node<T>* nextNodePtr);
	void setItem(const T& anItem);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	Node<T>* getNext() const ;
};

#include "Node.tpp"
#endif
