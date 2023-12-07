#pragma once

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

// This class defines a node, which will always be allocated on the heap
template<typename T>
class Node
{
public:
	Node(T newData = T()); // constructor - "constructs" a ListNode; initializes the object
	Node(const Node& copy);  // copy constructor - implicitly invoked copying a ListNode object during construction of 
	// another ListNode object, or when a ListNode object is passed-by-value;
	// the compiler generated one would be ok here as well! shallow copy performed!

	~Node();               // destructor - implicitly invoked when a ListNode object leaves scope;
	// the compiler generated one would be ok here as well!

	// we will not define an explicit overloaded assignment operator (=). We will
	// rely on the memberwise assignment generated by the compiler.

// getters
	T& getData();                // used to retrieve a copy of the data in the node
	Node* getNextPtr() const;      // used to retrieve a copy of the node's next pointer

	// setters
	void setData(const T& newData);            // used to modify the data in the node
	void setNextPtr(Node<T>* const pNewNext); // used to modify the node's next pointer

private:
	T mData;                   // represents a score
	Node* mpNext;            // should be set to NULL in the constructor
};

// constructor - "constructs" a ListNode; initializes the object
template<typename T>
Node<T>::Node(T newData)
{
	mData = newData;
	mpNext = nullptr;
}

// copy constructor - implicitly invoked copying a ListNode object during construction of 
// another ListNode object, or when a ListNode object is passed-by-value
template<typename T>
Node<T>::Node(const Node& copy)
{
	// shallow copy performed!
	mData = copy.mData;
	mpNext = copy.mpNext;
}

// destructor - implicitly invoked when a ListNode object leaves scope
template<typename T>
Node<T>::~Node()
{
	// Yes, these nodes are dynamically allocated, but delete will be invoked invoked by functions in List.
	// Hence, don't need to deallocate the heap memory inside of this destructor!
	cout << "Inside ListNode's destructor!" << endl;
}

template<typename T>
T& Node<T>::getData() // the const indicates "constant" function; can't modify the object's data members with this function
{
	return mData;
}

template<typename T>
Node<T>* Node<T>::getNextPtr() const // the const indicates "constant" function; can't modify the object's data members with this function
{
	return mpNext;
}

template<typename T>
void Node<T>::setData(const T& newData) // the const in this context ensures newData can't be modified
{
	mData = newData;
}

// the const in this context ensures pNewNext can't be modified;
// remember read as pNewNext is a constant pointer to a ListNode - the ListNode object is not const though!
template<typename T>
void Node<T>::setNextPtr(Node* const pNewNext)
{
	mpNext = pNewNext;
}