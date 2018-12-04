// File:        sorting.cpp
// Author:      Praneet Atwal, Justin Mang
// Date:        2016-02-20
// Description: File for CMPT 225 assignment #3 sorting functions and helpers

#include <iostream>
#include <string>

using namespace std;

// Selection Sort
// Takes a given array of type T and sorts in ascending order using Selection Sort Algorithm
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
int SelectionSort(T arr[], int n)
{
	int i, j, k = 0, count = 0; // counter for barometer operations
	T min;//smallest variable

	for(i = 0; i < n-1; i++)//start from 0 to n-1
	{
	min = arr[i];

	for(j = i+1; j < n; j++)//find the smallest
	{
  		count++;
  		if(min > arr[j])//compare
		{
			min = arr[j];//mark smallest
			k = j;//tag to be swapped
		} 	
	}

	if(min != arr[i])//if smaller found
	{
		arr[k] = arr[i];//swap
		arr[i] = min;//end swap
	}
	}
	return count;
}

// Quicksort
// Takes a given array of type T and sorts in ascending order using Quicksort Algorithm
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
int Quicksort(T arr[], int n)
{
	int count = 0;
	QuicksortHelper(arr, 0, n-1, count);
	return count;
}

// Takes a given array of type T and sorts in ascending order
// POST: VOID
// PARAM: T = given array of type T, low = integer value of index of lowest index, high = highest index, counter = barometer count function
template <class T>
void QuicksortHelper(T arr[], int low, int high, int& counter)
{
	int pIndex;//pivot
	if(low >= high)//base case
		return;
	pIndex = QSPartition(arr, low, high, counter);//pIndex sorted
	QuicksortHelper(arr, low, pIndex-1, counter);
	QuicksortHelper(arr, pIndex+1, high, counter);
}

// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, low = integer value of index of lowest index, high = highest index, counter = barometer count function
template <class T>
int QSPartition(T arr[], int low, int high, int& counter)
{ 
	T temp, pivot = arr[high];
	int i, pivotindex = low;

	for(i = low; i < high; i++){
	counter++;

	if(arr[i] <= pivot){
		temp = arr[pivotindex];//store value to potentially be swapped with pivot at end
		arr[pivotindex] = arr[i];//swap
		arr[i] = temp;			//end swap
		pivotindex++; //for swap with pivot
	}
	}

	temp = arr[pivotindex];//store pivot index for swap
	arr[pivotindex] = arr[high]; //pivot index is now pivot
	arr[high] = temp;//high is now pivot index
	return pivotindex;
}

// Randomized Quicksort
// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
int RQuicksort(T arr[], int n)
{
	int count = 0;
	RQuicksortHelper(arr, 0, n-1, count);
	return count;
}

// Takes a given array of type T and sorts in ascending order
// POST: VOID
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
void RQuicksortHelper(T arr[], int low, int high, int& counter)
{
	int pIndex;
	if(low>=high)
		return;
	pIndex=RQSPartition(arr, low, high, counter);//pIndex sorted
	RQuicksortHelper(arr, low, pIndex - 1, counter);
	RQuicksortHelper(arr, pIndex + 1, high, counter);
}

// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, low = integer value of index of lowest index, high = highest index, counter = barometer count function
template <class T>
int RQSPartition(T arr[], int low, int high, int& counter)
{
	int randomN = (low + rand()%(high-low+1));//randomly swap high with random index
	T temp = arr[randomN];
	arr[randomN] = arr[high];
	arr[high] = temp;

	T pivot = arr[high];
	int i, pivotindex = low;

	for(i = low; i < high; i++)
	{
		counter++;

		if(arr[i] <= pivot)
		{
			temp = arr[pivotindex];//store value to potentially be swapped with pivot at end
			arr[pivotindex] = arr[i];//swap
			arr[i] = temp;			//end swap
			pivotindex++; //for swap with pivot
		}
	}

	temp = arr[pivotindex];//store pivot index for swap
	arr[pivotindex] = arr[high]; //pivot index is now pivot
	arr[high] = temp;//high is now pivot index
	return pivotindex;
}

// Mergesort
// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
int Mergesort(T arr[], int n)
{
  int count = 0;
  MergesortHelper(arr, 0, n-1, n, count);
  return count;
}

// Takes a given array of type T and sorts in ascending order
// POST: VOID
// PARAM: T = given array of type T, low = integer value of index of lowest index, high = highest index, n = size of array, counter = barometer count function
template <class T>
void MergesortHelper(T arr[], int low, int high, int n, int& counter)
{
	if(low < high)
	{
		int mid = low + (high - low)/2;  
		MergesortHelper(arr, low, mid, mid - low + 1, counter);
		MergesortHelper(arr, mid + 1, high, high - mid, counter);
		Merge(arr, low, mid, high, n, counter);
	}
}

// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, low = integer value of index of lowest index, mid = middle index, high = highest index, n = size of array, counter = barometer count function
template <class T>
void Merge(T arr[], int low, int mid, int high, int n, int& counter)
{
  int i = low, j = mid + 1, k = low;
  T arrT[100];//temporary array

  while(i <= mid && j <= high)//compare and store new values in temporary array
  {
  	counter++;
  	if(arr[i] < arr[j])
	{
  	  arrT[k] = arr[i];
  	  i++;
  	}
  	else
  	{ 
  	  arrT[k] = arr[j];
  	  j++;
  	}
  	k++;
  }

  while(i <= mid)//store remaining values into temp. array
  {
  	arrT[k] = arr[i];
  	k++;
  	i++;
  }
  while(j <= high)
  {
  	arrT[k] = arr[j];
  	k++;
  	j++;
  }

  for(i = low; i <= high; i++)//transfer values from temporary array to existing array
  {
  	arr[i] = arrT[i];
  }
}

// Shell Sort
// Takes a given array of type T and sorts in ascending order
// POST:  Returns an integer value representing the number of barometer cycles
// PARAM: T = given array of type T, n = integer value of length of given array
template <class T>
int ShellSort(T arr[], int n)
{
	int count = 0;
	int j;

	//Narrow the array by 2 everytime
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; ++i)
		{
			T temp = arr[i];//element to be compared
			//compare element j until all interal elements compared, stop if exceeds interval set or temp value becomes greater than compared element
			for (j = i; j >= gap && temp < arr[j - gap]; j -= gap, count++)//reduce j by gap size (smallest reduction is 1)
			{
				arr[j] = arr[j - gap];//swap (move up) as long as temp is < compared
			}
			arr[j] = temp;//swap final element
		}//continue 
	}

	return count;
}
