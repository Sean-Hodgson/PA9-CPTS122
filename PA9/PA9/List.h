#pragma once

#include <iostream>

#include "Node.h"

using std::cin;
using std::cout;
using std::endl;

// This class defines a container for a list; it's a singly linked list
template<typename T>
class List
{
public:
	List();                     // default constructor; will always set mpHead to NULL
	List(const List& copyList); // copy constructor - implicitly invoked copying a List object during construction of 
	// another List object, or when a List object is passed-by-value - must perform a deep copy, 
	// which means create new memory for each node copied!
	~List();                    // destructor - implicitly invoked when a List object leaves scope

	List& operator= (const List& rhs); // overloaded assignment operator - must perform a deep copy, which means
	// create new memory (from the heap) for each node copied!

	// getter
	Node<T>* getHeadPtr() const;     // returns a copy of the address stored in mpHead

	// setter
	void setHeadPtr(Node<T>* const pNewHead); // modifies mpHead

	bool insertAtFront(const T& newData);     // inserts newData at the beginning or front of the list
	bool insertInOrder(const T& newData);     // inserts newData in ascending (smallest to largest) order
	bool insertAtEnd(const T& newData);       // inserts newData at the end of the list

	bool isEmpty();                            // determines if the list is empty  

	T deleteAtFront();                       // deletes the node at the front of the list
	bool deleteNode(const T searchValue);    // deletes the node with data == searchValue
	T deleteAtEnd();                         // deletes the node at the end of the list

	void printList(std::ostream& os);                          // visits each node, print the node's data - we could also overload the stream insertion << operator to print the list

private:
	Node<T>* mpHead; // pointer to the start or head of the singly linked list

	// yes, we can make member functions private as well
	Node<T>* makeNode(const T newData);    // will only call within insert functions
	void destroyList();                        // deletes each node to free memory; will call in the destructor
	void destroyListHelper(Node<T>* const pMem);    // we will use recursion to solve this problem!
};

template<typename T>
List<T>::List()
{
	mpHead = nullptr;
}

// copy constructor - implicitly invoked copying a List object during construction of 
// another List object, or when a List object is passed-by-value - must perform a deep copy, 
// which means create new memory for each node copied!
template<typename T>
List<T>::List(const List& copyList)
{
	// Check that there is something to copy
	if (copyList.mpHead == nullptr) {
		// The other list is empty so this list should be empty
		mpHead = nullptr;
	}
	else {
		// Copy all of the nodes one by one

		// Start with the first node
		Node<T>* node = new Node<T>(copyList.mpHead->getData());
		// Note that the new keyword allocates memory for the new node and initializes it at the same time so we don't have to set the node's data or next pointer because the constructor that we invoke with the new keyword already does that for us
		// Update the head
		mpHead = node;

		// Copy the rest of the nodes
		Node<T>* current = copyList.mpHead->getNextPtr();
		while (current != nullptr) {
			// Copy the node
			Node<T>* newNode = new Node<T>(current->getData());

			// Add the node to the end of the list
			node->setNextPtr(newNode);

			// Record the last node in the list
			node = newNode;
		}
	}
}

template<typename T>
List<T>::~List()                   // destructor - implicitly invoked when a List object leaves scope
{
	destroyList();
}

// this function must allocate new memory for each of the nodes in rhs to construct "this" object
template<typename T>
List<T>& List<T>::operator= (const List<T>& rhs) // overloaded assignment operator - must perform a deep copy
{
	// If we are assigning a list to itself, we don't need to do anything
	if (this == &rhs) {
		return (*this);
	}

	// Since this operator only ever gets invoked after we have initialized our variable, our list variable currently points to a list that must be deleted before we can replace our list with a copy of the other list's linked list
	destroyList(); // Cleanup the list we currently have

	// Copy the other list's linked list much in the same way as we did in the copy constructor

	// Check that there is something to copy
	if (rhs.mpHead == nullptr) {
		// The other list is empty so this list should be empty
		mpHead = nullptr;
	}
	else {
		// Copy all of the nodes one by one

		// Start with the first node
		Node<T>* node = new Node<T>(rhs.mpHead->getData());
		// Note that the new keyword allocates memory for the new node and initializes it at the same time so we don't have to set the node's data or next pointer because the constructor that we invoke with the new keyword already does that for us
		// Update the head
		mpHead = node;

		// Copy the rest of the nodes
		Node<T>* current = rhs.mpHead->getNextPtr();
		while (current != nullptr) {
			// Copy the node
			Node<T>* newNode = new Node<T>(current->getData());

			// Add the node to the end of the list
			node->setNextPtr(newNode);

			// Record the last node in the list
			node = newNode;
		}
	}

	// Return this list itself
	return (*this);
}

// getter
template<typename T>
Node<T>* List<T>::getHeadPtr() const     // returns a copy of the address stored in mpHead
{
	return mpHead;
}

// setter
template<typename T>
void List<T>::setHeadPtr(Node<T>* const pNewHead) // modifies mpHead
{
	mpHead = pNewHead;
}

// This function creates a new ListNode on the heap, and uses the ListNode constructor to initialize the node!
template<typename T>
bool List<T>::insertAtFront(const T& newData)     // inserts newData at the beginning or front of the list
{
	Node<T>* pMem = makeNode(newData);
	bool success = false;                   // C++ has built in bool types - false, true

	if (pMem != nullptr)
	{
		success = true; // allocated memory successfully
		// pMem is pointing to a ListNode object, but a List object does not have direct access to it; must use a setter!
		pMem->setNextPtr(mpHead);
		mpHead = pMem;
	}

	return success;
}

// insert newData in ascending order
template<typename T>
bool List<T>::insertInOrder(const T& newData)
{
	bool success = false;

	// Create a new node
	Node<T>* pMem = new Node<T>(newData);

	// Check that we allocated memory for the new node
	if (pMem != nullptr) {
		// Edge cases:
		// - The list is empty: the new node is the only node in the list
		// - The new node's data is less than the data in the first node: the new node should become the first node in the list

		// Check for an empty list
		if (mpHead == nullptr) {
			// Make the new node the first node in the list
			mpHead = pMem;
			// Check if the new node should become the first node in the list
		}
		else if (newData < mpHead->getData()) {
			// Make the new node the first node in the list
			pMem->setNextPtr(mpHead);
			mpHead = pMem;
		}
		else {
			// Find where to insert the node in the list
			Node<T>* previous = mpHead, * current = mpHead->getNextPtr();
			while (current != nullptr && current->getData() < newData) {
				// Move to the next node
				previous = current;
				current = current->getNextPtr();
			}

			// The node should be inserted between previous and current
			previous->setNextPtr(pMem);
			pMem->setNextPtr(current);
		}
	}

	return success;
}

// inserts newData at the end of the list
template<typename T>
bool List<T>::insertAtEnd(const T& newData)
{
	bool success = false;

	// Make a new node
	Node<T>* pMem = new Node<T>(newData);

	// Check that we allocated memory for the new node
	if (pMem != nullptr) {
		// Edge cases:
		// - The list is empty: the new node is the only node in the list

		// Check for an empty list
		if (mpHead == nullptr) {
			// Make the new node the first node in the list
			mpHead = pMem;
		}
		else {
			// Find the last node in the list
			Node<T>* current = mpHead;
			while (current->getNextPtr() != nullptr) {
				// Move to the next node
				current = current->getNextPtr();
			}

			// Add the new node to the end of the list
			current->setNextPtr(pMem);
		}
	}

	return success;
}

// determines if the list is empty;  
// returns true if the list is empty; false otherwise
template<typename T>
bool List<T>::isEmpty()
{
	return (mpHead == nullptr);
}

// deletes the node at the front of the list and returns a copy of the data
// precondition: list must not be empty
template<typename T>
T List<T>::deleteAtFront()
{
	T data;

	// Delete the first node and update the head pointer
	Node<T>* node = mpHead;
	data = node->getData();
	mpHead = node->getNextPtr();
	delete node;

	return data;
}

// deletes the node with data == searchValue;
// returns true if the value was found; false otherwise
// precondition: list must not be empty
template<typename T>
bool List<T>::deleteNode(const T searchValue)
{
	bool success = false;

	// Check that the list is not empty
	if (mpHead != nullptr) {
		// Check if the first node in the list should be deleted
		if (mpHead->getData() == searchValue) {
			// Delete the first node in the list and update the head pointer
			Node<T>* node = mpHead;
			mpHead = node->getNextPtr();
			delete node;
			success = true;
		}
		else {
			// Find the node to delete
			Node<T>* previous = mpHead, * current = mpHead->getNextPtr();
			while (current != nullptr && current->getData() != searchValue) {
				// Move to the next node
				previous = current;
				current = current->getNextPtr();
			}

			// Check if the node was found
			if (current != nullptr) {
				// Delete the node and update the previous node's next pointer
				previous->setNextPtr(current->getNextPtr());
				delete current;
				success = true;
			}
		}
	}

	return success;
}

// deletes the node at the end of the list and returns a copy of the data
// precondition: list must not be empty
template<typename T>
T List<T>::deleteAtEnd()
{
	int data = 0;

	// Check if there's only one node in the list
	if (mpHead->getNextPtr() == nullptr) {
		// Delete the first and only node and reset the head pointer
		data = mpHead->getData();
		delete mpHead;
		mpHead = nullptr;
	}
	else {
		// Find the second to last node in the list
		Node<T>* previous = mpHead, * current = mpHead->getNextPtr();
		while (current->getNextPtr() != nullptr) {
			// Move to the next node
			previous = current;
			current = current->getNextPtr();
		}

		// Delete the last node and update the previous node's next pointer
		data = current->getData();
		delete current;
		previous->setNextPtr(nullptr);
	}

	return data;
}

// visits each node, print the node's data
template<typename T>
void List<T>::printList(std::ostream& os)
{
	Node<T>* pCur = mpHead;

	while (pCur != nullptr)
	{
		os << pCur->getData() << endl;
		os << endl;
		pCur = pCur->getNextPtr();
	}
}


//////////// private member functions! //////////////

// allocates memory for a Listnode; initializes the memory with newData
template<typename T>
Node<T>* List<T>::makeNode(const T newData)    // will only call within insert functions
{
	Node<T>* pMem = new Node<T>(newData);  // ListNode constructor is invoked!

	return pMem;
}

// we created this function so that we could use recursion to delete the nodes!
template<typename T>
void List<T>::destroyListHelper(Node<T>* const pMem)
{
	if (pMem != nullptr)
	{
		destroyListHelper(pMem->getNextPtr());
		delete pMem;    // delete from the back of list to the front!
	}
}

// deletes each node to free memory; will call in the destructor
template<typename T>
void List<T>::destroyList()
{
	destroyListHelper(mpHead);
}