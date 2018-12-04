// File:        redblacktree.h
// Author:      Justin Mang and Praneet Atwal
// Date:        2016-03-17
// Description: Implementation of a RedBlackTree class and template Node class for use with CMPT 225 assignment #4

#ifdef _REDBLACKTREE_H_

#include <cstdlib>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class RedBlackTree
{
  private:
    Node<T>* root;
    int size;

    // recursive helper function for deep copy
    // creates a new node based on sourcenode's contents, links back to parentnode,
    //   and recurses to create left and right children
    Node<T>* RedBlackTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
	{
		if (node != NULL)
		  {
			// recurse on left child
			if (node->left != NULL)
			  InOrder(node->left, arr, arrsize, index);

			// visit current node
			arr[index] = node->data;
			index++;

			// recurse on right child
			if (node->right != NULL)
			  InOrder(node->right, arr, arrsize, index);
		  }
	}

    // recursive helper function for tree deletion
    // deallocates nodes in post-order
    void RedBlackTree<T>::RemoveAll(Node<T>* node)
	{
		if(node != NULL)
		{
			RemoveAll(node->left);
			RemoveAll(node->right);
			delete node;
		}
	}
	
    // Tree fix, performed after removal of a black node
    // Note that the parameter x may be NULL
    void RedBlackTree<T>::RBDeleteFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
	{

	}

    // Calculates the height of the tree
    // Requires a traversal of the tree, O(n)
    int RedBlackTree<T>::CalculateHeight(Node<T>* node) const
	{
		if (node == NULL)
			return -1;

		return 1 + max(CalculateHeight(node->left), CalculateHeight(node->right));
	}

  public:
    // default constructor
    RedBlackTree<T>::RedBlackTree()
	{
		root = null;
		size = 0;
	}

    // copy constructor, performs deep copy of parameter
    RedBlackTree<T>::RedBlackTree(const RedBlackTree<T>& rbtree)
	{
		CopyTree(rbtree);
	}

    // destructor
    // Must deallocate memory associated with all nodes in tree
    RedBlackTree<T>::~RedBlackTree()
	{
		if(root != NULL)
			RemoveAll(root);
	}

    // overloaded assignment operator
    RedBlackTree<T>::RedBlackTree<T>& operator=(const RedBlackTree<T>& rbtree)
	{
		if(rbtree.size == size)
		{
			T* temp1 = Dump(size);
			T* temp2 = rbtree.Dump(rbtree.size);
			int i = 0;
			while (i < size)
			{
				if(temp1[i] != temp2[i])
					return false;
				i += 1;
			}
		}
		return true;
	}

    // Accessor functions

    // Calls BSTInsert and then performs any necessary tree fixing.
    // If item already exists, do not insert and return false.
    // Otherwise, insert, increment size, and return true.
    bool RedBlackTree<T>::Insert(T item)
	{
		if(!Search(item))//if item does not exist then
		{
			BSTInsert(item);//insert item
			size += 1;
		} 
		else
			return false;
	}

    // Removal of an item from the tree.
    // Must deallocate deleted node after RBDeleteFixUp returns
    bool RedBlackTree<T>::Remove(T item)
	{

	}

    // deletes all nodes in the tree. Calls recursive helper function.
    void RedBlackTree<T>::RemoveAll()
	{
		RemoveAll(root);
	}

    // returns the number of items in the tree
    int Size() const
	{
		return size;
	}

    // returns the height of the tree, from root to deepest null child. Calls recursive helper function.
    // Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
    int Height() const
	{
		if(root == NULL)
			return 0;
		else
		{
			return CalculateHeight(root);
		}
	}

    // returns a pointer to the root of the tree
    // NOTE: This will be used only for grading.
    // Providing access to the tree internals is dangerous in practice!
    Node<T>* RedBlackTree<T>::GetRoot() const
    {
      return this->root;
    }
};

#endif