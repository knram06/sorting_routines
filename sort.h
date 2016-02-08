
#ifndef SORT_H
#define SORT_H

#include "heapsort.h"

// helper function
template <class T>
void swap(T& a, T& b)
{
    T temp = b;
    b = a;
    a = temp;
}

// keeping return as void for now
// takes in an array and size -- In place sorting
template <class T>
void insertion_sort(T* inpArray, const int numElem)
{
    T key;

    // we start from index 1
    for (int i = 1; i < numElem; i++)
    {
        int index = i;

        // this needs operator= to be defined?
        key = inpArray[index];
        while (index > 0 && inpArray[index - 1] > key)
        {
            inpArray[index] = inpArray[index - 1];
            index--;
        } // end of while loop which checks inside already sorted array

        // attempt at optimization
        // check if index was actually changed
        // if so, then write the updated value
        if (index != i)
            inpArray[index] = key;

    } // end of for loop through elements
}

template <class T>
void selection_sort(T* inpArray, const int size)
{
    for (int i = 0; i < size; i++)
    {
        int minLoc = i;
        for (int j = minLoc; j < size - 1; j++)
        {
            if (inpArray[minLoc] > inpArray[j + 1])
                minLoc = j + 1;
            //else
            //    minLoc = j + 1;
        }

        // attempt at optimization
        // check if minLoc was actually changed
        // if so, only then swap?
        if (minLoc != i)
            swap(inpArray[i], inpArray[minLoc]);
    }
}

template <class T>
void merge(T* inpArray, const int iStart, const int iEnd, const int pivotIndex)
{
    const int size = iEnd - iStart + 1;
    int i = iStart;
    int j = pivotIndex + 1;

    T* dupArray = new T[size];
    for(int k = 0; k < size; k++)
    {
        if(i <= pivotIndex && j <= iEnd)
        {
            if(inpArray[i] < inpArray[j])
            {
                dupArray[k] = inpArray[i];
                i++;
            }
            else
            {
                dupArray[k] = inpArray[j];
                j++;
            }
        } // end of bounds check for i and j

        else
        {
            // if j has run over its elements and if i is left with elements
            if(i <= pivotIndex)
            {
                dupArray[k] = inpArray[i];
                i++;
            }
            // if i has run over its elements and if i is left with elements
            else if( j <= iEnd)
            {
                dupArray[k] = inpArray[j];
                j++;
            }
        } // end of else
    }

    // copy back temp result into array
    for(int k = 0; k < size; k++)
        inpArray[iStart + k] = dupArray[k];

    delete [] dupArray;
}

template <class T>
void split_merge(T* inpArray, const int iStart, const int iEnd)
{
    if(iStart < iEnd)
    {

        int iMiddle = (iStart + iEnd) / 2;
        split_merge<T>(inpArray, iStart, iMiddle);
        split_merge<T>(inpArray, iMiddle+1, iEnd);

        merge<T>(inpArray, iStart, iEnd, iMiddle);
    }
}

template <class T>
void merge_sort(T* inpArray, const int size)
{
    split_merge(inpArray, 0, size-1);
}

// non-recursive merge sort
template <class T>
void non_recursive_merge_sort(T* inpArray, const int size)
{
    for(int width = 2; width <= size; width *= 2)
    {
        for(int i = 0; i < size; i += width)
        {
            int iStart = i;
            int iEnd = i+width-1;
            if(iEnd > size-1)
                iEnd = size-1;
            int pivot = (iStart+iEnd)/2;

            if(iStart < iEnd)
                merge(inpArray, iStart, iEnd, pivot); 
        }
    }
}

// practice code may have been better? No extra while loops?
// but minor optimization point
template <class T>
void quick_sort(T* inpArray, const int iStart, const int iEnd)
{
    if(iStart < iEnd)
    {
        const int pivotIndex = (iStart + iEnd) / 2;
        const T pivotValue = inpArray[pivotIndex];

        int i = iStart, j = iEnd;
        while(i < j)
        {
            while(inpArray[i] < pivotValue)
                i++;
            while(inpArray[j] > pivotValue)
                j--;

            if(i <= j)
            {
                swap(inpArray[i], inpArray[j]);

                // update the pivotIndex
                //if(i == pivotIndex)
                //    pivotIndex = j;
                //else if (j == pivotIndex)
                //    pivotIndex = i;

                i++; j--;
            }
        }

        quick_sort(inpArray, iStart, j);
        quick_sort(inpArray, i, iEnd);
    }
}

template <class T>
void quicksort(T* inpArray, const int size)
{
    quick_sort(inpArray, 0, size-1);
}

// heapsort
template <typename T>
void heapsort(T* inpArray, const int size)
{
    MaxHeap<T> mh(inpArray, size);
    mh.heapSort();
}


#endif
