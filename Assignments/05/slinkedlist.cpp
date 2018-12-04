// File:        slinkedlist.cpp
// Author:      Justin Mang, Praneet Atwal
// Date:        April 1, 2016
// Description: Implementation of a template singly-linked-list class for CMPT 225 assignment 5

#ifdef _SLINKEDLIST_H_

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll)
{
	if(!ll.IsEmpty())//determine is list to copy is populated (at least 1 element to copy)
	{
		DeleteList();//delete current list
		Node<T>* temp;//temporary pointer to iterate through existing list
		Node<T>* newNode;//temporary pointer to create copied list
		front = newNode;//assign first item to front
		
		temp = ll.front;//grab referenced list's front
		while(temp != NULL)
		{
			newNode = new Node<T>*;//node to be added
			newNode->data = temp->data;//copy data
			newNode->next = temp->next;//and pointer to newNode
			temp = temp->next;//iterate to next node or NULL
			size += 1;
		}

		back = newNode;//assign last item to back
	}
	
}

// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void SLinkedList<T>::SLinkedList<T>::DeleteList()
{
	if(!IsEmpty())//determine is list to copy is populated (at least 1 element to delete)
	{
		Node<T>* temp;//temporary pointer to delete list elements with
		temp = front;
		
		while(temp != NULL)
		{
			front = front->next;//iterate
			delete temp;
			temp = front;
		}
		delete back;
		front = NULL;
		back = NULL;
		size = 0;
	}
}


// default constructor
template <class T>
SLinkedList<T>::SLinkedList()
{
	front = NULL;
	back = NULL;
	size = 0;
}

// copy constructor, performs deep copy of list elements
template <class T>
SLinkedList<T>::SLinkedList(const SLinkedList& ll)
{
	CopyList(ll);
}

// destructor
template <class T>
SLinkedList<T>::~SLinkedList()
{
	DeleteList();
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at front
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertFront(T item)
{
	Node<T>* newItem = new Node<T>*(item);//item to be stored
	if(isEmpty())
	{
		front = newItem;
		back = newItem;
		size += 1;
	}
	else
	{
		newItem->next = front;//point item's next to front's item
		front = newItem;//front now newItem
		size += 1;
	}
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void SLinkedList<T>::InsertBack(T item)
{
	Node<T>* newItem = new Node<T>*(item);//item to be stored
	if(isEmpty())
	{
		front = newItem;
		back = newItem;
		size += 1;
	}
	else
	{
		back->next = newItem;//point back to newItem
		back = newItem;//back now newItem
		size += 1;
	}
}

// Removes the first occurrence of the supplied parameter
// Removes and returns true if found, otherwise returns false if parameter is not found or list is empty
template <class T>
bool SLinkedList<T>::Remove(T item)
{
	if((!IsEmpty()) && Contains(item))
	{
		if(size == 1)//if one item delete entire list
		{
			DeleteList();
			return true;
		}
		else//search for item, fix pointers, delete item
		{
			
			Node<T>* current;//item to be examined
			Node<T>* ahead;//item ahead of current
			Node<T>* nodeToDelete;//used for deletion
			current = front;
			ahead = current;
			if(current->data == item)//handles case for if front is the item to be deleted
			{
				nodeToDelete = front;
				front = front->next;
				delete nodeToDelete;
				size -= 1;
				return true;
			}
			else
			{
				while(current != NULL)
				{
					ahead = current->next;//grab current->next
					if(ahead->data == item)//if item ahead of current is target
					{
						if(ahead == back)//handles case for when item to remove is back
						{
							back == current;
						}
						current->next = ahead->next;//reassign pointers
						nodeToDelete = current->next;
						delete nodeToDelete;
						size -= 1;
						return true;
					}
					current = current->next;//advance current item to be examined
				}
			}
		}

	}
	return false;
}

// Removes all items in the list
template <class T>
void SLinkedList<T>::RemoveAll()
{
	if(!IsEmpty())//determine if list contains at least 1 element
	{
		Node<T>* temp;//temporary pointer to iterate with
		temp = front;
		while(temp != NULL)
		{
			temp = temp->next;//iterate
			delete front;
			front = temp;
			size -= 1;
		}
		front = NULL;
		back = NULL;
	}
}

// ACCESSORS

// Returns size of list
template <class T>
int SLinkedList<T>::Size() const
{
	return size;
}

// Returns whether the list is empty
template <class T>
bool SLinkedList<T>::IsEmpty() const
{
	if(size == 0)
		return true;
	else
		return false;
}

// Returns existence of item
template <class T>
bool SLinkedList<T>::Contains(T item) const
{
	if(!IsEmpty())
	{
		Node<T>* temp;
		temp = front;
		while(temp != NULL)
		{
			if(temp->data = item)
			{
				return true;
			}
			temp = temp->next;//iterate
		}
	}
	return false;
}

// Returns a pointer to the in-place list item or NULL if item not found
template <class T>
T* SLinkedList<T>::Retrieve(T item)
{
	if(!IsEmpty())
	{
		Node<T>* temp;
		temp = front;
		while(temp != NULL)
		{
			if(temp->data = item)
			{
				return temp;//ptr to data?
			}
			temp = temp->next;//iterate
		}
	}
	return NULL;
}

// Returns a vector containing the list contents using push_back
template <class T>
vector<T> SLinkedList<T>::Dump() const
{
	vector<T> t1;//reverse vector
	vector<T> t2;//correct order vector
	Node<T>* temp;//data grabber
	temp = front;//grab front
	while(temp != NULL)
	{
		t1.push_back(temp->data);//store in reverse order
		temp = temp->next;//iterate till last item
	}
	for (int i = 0; i < t1.size(); i++)//store reverse vector in correct order in new vector
	{
		t2.push_back(t1[i]);
	}
	return t2;
}

// OVERLOADED OPERATORS

// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
SLinkedList& SLinkedList<T>::operator=(const SLinkedList& ll)
{
	if(front != ll.front)
	{
		CopyList(ll);
	}
	return *this;
}

#endif