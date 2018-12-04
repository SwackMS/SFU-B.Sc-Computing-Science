// File:        dlinkedlist.cpp
// Author:      Justin Mang
// Date:        January 30, 2016
// Description: Definition of a template doubly-linked-list class for CMPT 225 assignment 2

#ifdef _DLINKEDLIST_H_

#include <cstdlib>
#include <stdexcept>
#include <string>

using namespace std;

// helper function for deep copy
// Used by copy constructor and operator=
template <class T>
void DLinkedList<T>::CopyList(const DLinkedList& ll)
{
	if(!ll.IsEmpty())
	{
		DeleteList();//delete existing list

		Node<T> *newItem = new Node<T>(ll.front->data);//create newitem using data from other list's first item

		front = newItem;//new item is at front of list

		size += 1;//increase for first item

		Node<T> *temp1 = ll.front; //temp1 marks progress for source
		Node<T> *temp2 = front;//temp2 marks progress for new list
		while (temp1->next != NULL)
		{	
			temp1 = temp1->next;//get next item to be copied
			newItem = new Node<T>(temp1->data);//create new node
			newItem->prev = temp2;
			temp2->next = newItem;
			temp2 = newItem;
			size += 1;
		}
		back = newItem;
		//delete newItem;
		//delete temp1;
		//delete temp2;
	}
	
}

// helper function for deep delete
// Used by destructor and copy/assignment
template <class T>
void DLinkedList<T>::DeleteList()
{
	if(!IsEmpty())
	{
		Node<T> *temp = front;
		while (temp != NULL)
		{
			temp = front->next;
			delete front;
			front = temp;
		}
		front = NULL;
		back = NULL;
		size = 0;
	}
}

// default constructor
template <class T>
DLinkedList<T>::DLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

// copy constructor, performs deep copy of list elements
template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList& ll)
{
	CopyList(ll);
}
// destructor
template <class T>
DLinkedList<T>::~DLinkedList()
{
	DeleteList();
}

// MUTATORS

// Inserts an item at the front of the list
// POST:  List contains item at position 0
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertFront(T item)
{
	Node<T> *temp = new Node<T>(item);
	if(IsEmpty())
	{
		front = temp;
		back = temp;
		size += 1;
	}
	else
	{
		temp->next = front;
		front->prev = temp;
		front = temp;
		size += 1;
	}
	//delete temp;
}

// Inserts an item at the back of the list
// POST:  List contains item at back
// PARAM: item = item to be inserted
template <class T>
void DLinkedList<T>::InsertBack(T item)
{
	Node<T> *temp = new Node<T>(item);
	if(IsEmpty())
	{
		front = temp;
		back = temp;
		size += 1;
	}
	else
	{
		temp->prev = back;
		back->next = temp;
		back = temp;
		size += 1;
	}
	//delete temp;
}

// Inserts an item in position p (0-indexed)
// Throws exception for invalid index
// PRE:   0 <= p <= size
// POST:  List contains item at position p
// PARAM: item = item to be inserted, p = position where item will be inserted
template <class T>
void DLinkedList<T>::InsertAt(T item, int p)
{
	if(p >= 0 && p < size)
	{
		//if(p == 0 || p == (size - 1))
		//{
		//	if(p == 0)
		//		InsertFront(item);
		//	else
		//		InsertBack(item);
		//}
		//else
		//{
			Node<T> *newItem = new Node<T>(item);
			Node<T> *temp = front;
			Node<T> *temp1;
			for (int i = 0; i < p; i++)
			{
				temp=temp->next;
			}
			temp1 = temp->prev;
			temp1->next = newItem;
			temp->prev = newItem;
			newItem->prev=temp1;
			newItem->next=temp;
			
			if(p == size-1)
				back=temp;
			if(p == 0)
				front=newItem;
			size += 1;
		//}
	}
	else
	{
		throw std::exception("Invalid Index");
	}
	
}

// Removes and returns an item from position p (0-indexed)
// Throws exception if list is empty or index invalid
// PRE:   0 <= p < size
// POST:  Item is removed from list
// PARAM: p = position from where item will be removed
template <class T>
T DLinkedList<T>::RemoveAt(int p)
{
	Node<T> *result;
	if(!(IsEmpty()) && (p >= 0 && p < size))
	{	
		Node<T> *temp;
		Node<T> *temp1;
		Node<T> *temp2;

		temp = front;

		for (int i = 0; i < p; i++)//if necessary move to appropriate index
		{
			temp = temp->next;
		}
		result = new Node<T>(temp->data);//grab data from node to be deleted
		temp1 = temp->prev;
		temp2 = temp->next;
		if (temp1 != NULL && temp2 != NULL)//at least 3 elements and not front or back
		{
			temp1->next = temp2;
			temp2->prev = temp1;
		}
		else
		{
			if(temp1==NULL)
			{
				temp2->prev = NULL;
				front=temp2;
			}
			if(temp2==NULL)
			{
				temp1->next = NULL;	
			}
		}
		delete temp;
		size -= 1;
	}
	else
	{
		throw std::exception("Invalid Index");
	}
	return result->data;
}

// Removes duplicates from the list, preserving existing order of remaining items.
// The first occurrence of any duplicate (relative to the front of the list)
//   is the one which remains.
// We have not yet learned about efficiency so you may implement this in any way
//   as long as the resulting list satisfies the requirement above.
// PRE:   
// POST:  List contains no duplicates, front and back point to the appropriate nodes
// PARAM: 
template <class T>
void DLinkedList<T>::RemoveDuplicates()
{
	if (!IsEmpty())
	{
		Node<T> *temp;
		Node<T> *compare;
		Node<T> *remove;

		compare = front;
		temp = compare;
		while (temp->next != NULL)
		{
			temp = compare->next;
			while(temp->next !=NULL)
			{
				remove = temp;//for deletion if needed
				if(compare->data == temp->data) //if data the same then delete
				{
					if(remove->next == NULL)
					{
						back = remove->prev;
					}
					delete remove;
					size -= 1;
				}
				temp = temp->next;//point to next comparison
			}
			compare = compare->next;
		}
	}
}

// ACCESSORS

// Returns size of list
template <class T>
int DLinkedList<T>::Size() const
{
	return size;
}

// Returns whether the list is empty
template <class T>
bool DLinkedList<T>::IsEmpty() const
{
	if (size == 0)
		return true;
	else
		return false;
}

// Returns existence of item
template <class T>
bool DLinkedList<T>::Contains(T item) const
{
	Node<T> *temp;
	Node<T> *compare = new Node<T>(item);
	temp = front;

	while(temp != NULL)
	{		
		if(compare->data == temp->data) //if data the same then return true
		{
			return true;
		}
		temp = temp->next;//point to next comparison
	}
	return false;
}

// Returns item at index (0-indexed)
// Throws exception for invalid index
template <class T>
T DLinkedList<T>::ElementAt(int p) const
{
	if((!IsEmpty()) && (p >= 0 && p < size))
	{	
		Node<T> *temp;
		Node<T> *result;
		temp = front;
		for (int i = 0; i < p; i++)
		{
			temp = temp->next;
		}
		result = new Node<T>(temp->data);
		//delete temp;
		return result->data;
	}
	else
	{
		throw std::exception("Invalid Index");
	}
}

// OVERLOADED OPERATORS

// overloaded assignment operator
// must work in the following cases:
// list2 = list1 -> general case
// list2 = list2 -> should do nothing
template <class T>
DLinkedList<T>& DLinkedList<T>::operator = (const DLinkedList& ll)
{
	if (front != ll.front)
	{
		CopyList(ll);
	}
	return *this;
}
#endif