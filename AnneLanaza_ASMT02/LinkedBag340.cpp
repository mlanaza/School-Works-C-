//	LinkedBag340.cpp
//	Created by: Anne Lanaza, Jesani May Macatbag

#include <cstddef>
#include <ctime> // to utilize time
#include "Node.h"
#include "LinkedBag.h"


template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340() {
	if (!this->isEmpty()) {
		Node<ItemType>* secNodePtr = headPtr->getNext();

		if (secNodePtr != nullptr) {
			this->remove(secNodePtr->getItem());
			return true;
		}

	}
	return false;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& anEntry) {

	if (!this->isEmpty()) { 
		Node<ItemType>* curPtr = headPtr->getNext();
		Node<ItemType>* newNodePtr = new Node<ItemType>;
		newNodePtr->setItem(anEntry);
		newNodePtr->setNext(nullptr);

		while (curPtr->getNext() != nullptr) { //moves the curPtr until the end
			curPtr = curPtr->getNext();
		}

		curPtr->setNext(newNodePtr);
		itemCount++;

		return true;
	}

	return false;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
	Node<ItemType>* curPtr = headPtr;
	int count = 0;

	while (curPtr != nullptr) {
		count++;
		curPtr = curPtr->getNext(); //moves pointer
	}

	return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
	static Node<ItemType>* curPtr = headPtr;
	int count = 0;

	if (curPtr == nullptr) {
		curPtr = headPtr; //resets the ptr for later use
		return 0;
	}
	else {
		curPtr = curPtr->getNext();
		return (count += this->getCurrentSize340Recursive() + 1);
	}

	return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& anEntry) const {
	static Node<ItemType>* curPtr = headPtr;
	int count = 0;

	if (curPtr == nullptr) {
		curPtr = headPtr; //resets the ptr for later use
		return 0;
	}
	else if (curPtr->getItem() == anEntry) { //when ptr is equals to anEntry
		curPtr = curPtr->getNext();
		return (count += this->getFrequencyOf340Recursive(anEntry) + 1);
	}
	else {
		curPtr = curPtr->getNext(); 
		return (count += this->getFrequencyOf340Recursive(anEntry)); 
	}

	return count;
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
	Node<ItemType>* curPtr = headPtr;
	ItemType type = curPtr->getItem();
	std::srand((int)std::time(0));
	int randNode = (std::rand() % itemCount) + 1;
	int i = 1;

	while (i != randNode) {
		curPtr = curPtr->getNext();
		i++;
	}

	type = curPtr->getItem();

	this->remove(type);

	return type;
}
