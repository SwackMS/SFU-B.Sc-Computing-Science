// File:        hashtable.cpp
// Author:      Justin Mang, Praneet Atwal
// Date:        April 1, 2016
// Description: Implementation of a hash table class for CMPT 225 assignment 5
//              must include hashtableprivate.h file for additional private member functions added by student

#pragma once

#include <cstdlib>
#include <math.h> // needed for Hash function
#include <string>
#include <vector>
#include "slinkedlist.h"
#include "useraccount.h"
#include "hashtable.h"

using namespace std;

// hash function, uses Horner's method
// Assume input string consists only of lower-case a to z
int HashTable::Hash(string input) const
{
}

// helper function to find smallest prime number greater than supplied parameter
int HashTable::SmallestPrime(int n) const
{
}

// helper function to determine whether a number is prime
bool HashTable::IsPrime(int n) const
{
}

// Resizes the hashtable into a larger array.
// Return false if n is smaller than current array size or if n is negative.
// Else, set array size to the smallest prime number larger than n
//   and re-hash all contents into the new array, delete the old array and return true.
bool HashTable::Resize(int n)
{
}

// write your own private member functions in the following file
#include "hashtableprivate.h"


// default constructor
// creates an array of size 101
HashTable::HashTable()
{
}

// parameterized constructor
// creates an array of size = smallest prime number > 2n
HashTable::HashTable(int n)
{
}

// copy constructor
// Creates deep copy of sourceht
HashTable::HashTable(const HashTable& sourceht)
{
}

// destructor
HashTable::~HashTable()
{
}

// overloaded assignment operator
HashTable& HashTable::operator=(const HashTable& sourceht)
{
}

// Insertion
// If item does not already exist, inserts at back of hashed list and returns true
//   otherwise returns false
// If load factor (before insertion) is above 2/3, expand into a new
//   table of smallest prime number size at least double the present table size
//   and then insert the item.
bool HashTable::Insert(UserAccount acct)
{
}

// Removal
// If item exists, removes and returns true
//   otherwise returns false
bool HashTable::Remove(UserAccount acct)
{
}

// Search
// Returns true if item exists, false otherwise
bool HashTable::Search(UserAccount acct) const
{
}

// Retrieval
// Returns a pointer to a UserAccount object inside the hash table (linked list)
//   if a matching parameter is found, otherwise return NULL
UserAccount* HashTable::Retrieve(UserAccount acct)
{
}

// Returns the number of items stored in the hash table
int HashTable::Size() const
{
}

// Returns the size of the underlying array
int HashTable::MaxSize() const
{
}

// Returns the load factor as size / maxsize.
// Note that due to separate chaining, load factor can be > 1.
double HashTable::LoadFactor() const
{
}


