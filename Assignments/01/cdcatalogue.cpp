// File:        cdcatalogue.cpp
// Author:      Justin Mang
// Date:        2016-01-18
// Description: Implementation of a CDCatalogue class to be used for CMPT 225 Assignment #1

#include "cdcatalogue.h"
#include <string>
using namespace std;

// Default constructor
CDCatalogue::CDCatalogue()
{
	maxsize = 4;
	numcds = 0;
	cds = new CD[maxsize];
}

// Parameterized constructor
CDCatalogue::CDCatalogue(const CDCatalogue& cat)
{
	maxsize = cat.maxsize;
	numcds = cat.numcds;
	CopyArray(cat);
}

// Destructor
CDCatalogue::~CDCatalogue()
{
	delete[] cds;
}

// Helper method for copy constructor
// Performs deep copy of dynamic array
void CDCatalogue::CopyArray(const CDCatalogue& cat)
{
	cds = new CD[cat.maxsize];
	for (int i = 0; i < cat.numcds; i++)
	{
		cds[i] = cat.cds[i];
	}
}
//////////////////////////
// Mutators / Accessors //
//////////////////////////

// Insert - performs a set insertion with the CD catalogue
// Inserts CD and returns true if CD is not already in the catalogue
// Does not insert and returns false if a CD with a matching artist and album name
//   already exists in the registry
// If the array is already filled before the insertion occurs, then
//   first create a new dynamic array double the size of the old array,
//   copy all CD objects from old array to new array,
//   deallocate memory associated with the old array,
//   and insert the new CD and return true.
// POST:  catalogue contains CD
// PARAM: disc = item to be inserted, its fields should not be empty string
// NOTE:  since overloaded assignment operator has not been defined,
//          "insertion" will mean updating all fields of the CD at the appropriate index
bool CDCatalogue::Insert(CD disc)
{
	if (Find(disc) != -1)
	{
		return false;
	}
	else
	{
		//Expand array if necessary
		if (numcds == maxsize)
		{
			maxsize = maxsize * 2;
			CD* temp = new CD[maxsize];
			for (int i = 0; i < numcds; i++)
			{
				temp[i] = cds[i];
			}
			delete[] cds;
			cds = temp;
		}
		cds[numcds] = disc;
		numcds = numcds + 1;
		return true;
	}
}

// Remove - performs a set removal with the CD catalogue
// Removes a CD with all matching parameters if one exists in the catalogue
// Returns false if a CD with the same parameters does not exist in the catalogue
// POST:  catalogue does not contain CD
// PARAM: disc = item to be removed, its fields should not be empty string
// NOTE:  "removal" if successful will be done by updating the parameters of the
//          CD at the appropriate index using the parameters of the CD in
//          the last valid index of the collection; then decrements count and returns true;
bool CDCatalogue::Remove(CD disc)
{
	if (Find(disc) != -1)
	{
		for (int i = Find(disc); i < numcds-1; i++)
		{
			cds[i] = cds[i + 1];
		}
		numcds = numcds - 1;
		return true;
	}
	return false;
}

// Locates the array index of a CD with matching parameters
// Returns -1 if no CD with matching parameters exists in the catalogue
// PARAM: disc = item to be located, its fields should not be empty string
int CDCatalogue::Find(CD disc) const
{
	for (int i = 0; i < numcds; i++)
	{
		if (disc == cds[i])
		{
			return i;
		}
	}
	return -1;
}

// Removes all CDs from the catalogue with artist matching the provided argument
// Returns false if there are not matching CDs or input is empty string,
//   otherwise returns true if at least one CD is removed
// Remaining items may appear in the array in any order, with the requirement that
//   there are no "empty" spaces in the array (i.e. an array with 5 items must occupy indices 0-4)
// POST:  catalogue contains no instances of CDs with the supplied artist name
// PARAM: dontlikeanymore = name of artist whose CDs should be removed from the catalogue
bool CDCatalogue::Boycott(string dontlikeanymore)
{
	bool flag = false;
	for (int i = 0; i < numcds; i++)
	{
		if (dontlikeanymore == cds[i].GetArtist())
		{
			Remove(cds[i]);
			flag = true;
		}
	}
	return flag;
}

// Returns the number of CDs in the catalogue
int CDCatalogue::Count() const
{
	return numcds;
}

////////////////////
// Set operations //
////////////////////

// Returns the set union of this and cat
// POST: union contains CD of this and cat, with no duplicate CDs (both parameters matching).
CDCatalogue CDCatalogue::Join(const CDCatalogue& cat) const
{
	CDCatalogue tempCat;
	//No comparison required, add CDs to new catalogue
	for (int i = 0; i < (numcds); i++)
	{
		tempCat.Insert(cds[i]);
	}
	for (int j = 0; j < (cat.numcds); j++)
	{
		tempCat.Insert(cat.cds[j]);
	}
	return tempCat;
}

// Returns the set intersection of this and cat
// POST: intersection contains CDs in both this and cat (both parameters matching).
CDCatalogue CDCatalogue::Common(const CDCatalogue& cat) const
{
	CDCatalogue tempCat;
	//Determine which catalogue is larger, then compare CDs
	if (numcds >= cat.numcds)
	{
		for (int i = 0; i < numcds; i++)
		{
			for (int j = 0; j < cat.numcds; j++)
			{
				if (cds[i] == cat.cds[j])
				{
					tempCat.Insert(cds[i]);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < cat.numcds; i++)
		{
			for (int j = 0; j < numcds; j++)
			{
				if (cat.cds[i] == cds[j])
				{
					tempCat.Insert(cat.cds[i]);
				}
			}
		}
	}
	return tempCat;
}

// Returns the set difference of this and cat
// CDs in both catalogues must have a full set of matching parameters
//   for a CD to be removed in the split.
// POST: difference contains CDs in this but not also in cat
CDCatalogue CDCatalogue::Split(const CDCatalogue& cat) const
{
	CDCatalogue tempCat;
		//Compare this catalogue
		for (int i = 0; i < numcds; i++)
		{
			if (cat.Find(cds[i]) == -1)
			{
				tempCat.Insert(cds[i]);
			}		
		}
		//Compare cat catalogue -NOT NEEDED
		/*
		for (int j = 0; j < cat.numcds; j++)
		{
			if (Find(cat.cds[j]) == -1)
			{
				tempCat.Insert(cat.cds[j]);
			}
		}*/
	return tempCat;
}
