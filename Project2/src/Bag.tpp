// Methods from Frank M. Carrano and Tim Henry.
// This file is included in "Bag.hpp"

/** @file Bag.cpp */

#include <algorithm>
#include <cstddef>

template<typename T>
Bag<T>::Bag() : headPtr(nullptr), itemCount(0) {}

template<typename T>
int Bag<T>::size() const {
	return itemCount;
}

template<typename T>
bool Bag<T>::isEmpty() const {
	return itemCount == 0;
}

template<typename T>
bool Bag<T>::add(const T& newEntry) {
	Node<T>* nextNodePtr = new Node<T>(newEntry, headPtr);
	headPtr = nextNodePtr;
	itemCount++;
	return true;
}

template<typename T>
void Bag<T>::clear() {
	Node<T>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = headPtr;
	}


	itemCount = 0;
}

template<typename T>
Node<T>* Bag<T>::getPointerTo(const T& target) const {
	bool found = false;
	Node<T>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (target == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	}

	return curPtr;
}

template<typename T>
bool Bag<T>::contains(const T& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}

template<typename T>
int Bag<T>::getFrequencyOf(const T& anEntry) const {
	int frequency = 0;
	int counter = 0;
	Node<T>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		}

		counter++;
		curPtr = curPtr->getNext();
	}
	return frequency;
}

template<typename T>
std::vector<T> Bag<T>::toVector() const {
	std::vector<T> bagContents;
	Node<T>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}

	return bagContents;
}

template<typename T>
Bag<T>::~Bag() {
	   clear();
}
