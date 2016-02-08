
#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <cassert>

// Node class was not needed (yet? for simple cases?)
//template <typename T>
//class Node
//{
//    private:
//        // making the default constructor private?
//
//    public:
//        Node *parent, *left, *right;
//        T val;          // investigate having this as pointer or reference?
//        //static int numNodes = 0;
//
//        // constructor
//        Node() : parent(NULL), left(NULL), right(NULL), val(0)
//        {};
//
//        // takes in a value to store in the Node
//        Node(T inpVal) : parent(NULL), left(NULL), right(NULL), val(inpVal)
//        {};
//
//};

template <typename T>
class MaxHeap
{
    private:
        // adjusted for 0-based indexing
        int left(const int i) {return 2*i + 1;}
        int right(const int i) {return 2*i + 2;}

        // adjust for whether i is even or odd
        int parent(const int i) {return (i % 2) ? (i/2) : (i/2)-1 ;}

        // swap for exchanging values
        void swap(T& a, T& b)
        {
            T temp = a;
            a = b;
            b = temp;
        }

        // build max-heap
        void build_max_heap()
        {
            int startIndex = (heapSize / 2) - 1;
            for(int i = startIndex; i >= 0; i--)
                max_heapify(i);
        }

        // function for max-heapify
        void max_heapify(const int i)
        {
            const int l = left(i);
            const int r = right(i);

            const int heapExtent = heapSize - 1;
            int largest = i;

            // pick the index corresponding to the max 
            // among i and its left and right elements
            if ((l <= heapExtent) && (inpArray[l] > inpArray[i]) )
                largest = l;

            // should this be an else if
            if ((r <= heapExtent) && (inpArray[r] > inpArray[largest]) )
                largest = r;

            if (largest != i)
            {
                swap(inpArray[largest], inpArray[i]);
                max_heapify(largest);
            }

        }


    // keeping it public for now
    public:
        T* inpArray;
        const int arraySize;
        int heapSize;

        // constructor
        MaxHeap () : inpArray(NULL), arraySize(0), heapSize(0) {};

        // other versions of the constructor
        MaxHeap (T* inp, const int size)
            : inpArray(inp), arraySize(size), heapSize(size)
        {
            build_max_heap();
            // doing dynamic allocation
            //inpArray = new Node<T>*[arraySize];

            //for(int i = 0; i < arraySize; i++)
            //{
            //    inpArray[i] = new Node<T>(inp[i]);
            //    heapSize++;
            //}

        }

        //void heapSort(T* outArray, const int size)
        void heapSort()
        {
            // check that inputsize matches arraysize?
            //assert(arraySize == size);

            for(int i = heapSize-1; i >= 1; i--)
            {
                swap(inpArray[i], inpArray[0]);
                //outArray[i] = inpArray[0];

                // this is necessary to make sure max_heapify does not
                // affect the rest of the heap
                heapSize--;
                max_heapify(0);
            }

            // fill in the 0th element for outArray
            //outArray[0] = inpArray[0];
        }

        // print the heap
        //void printHeap() const
        //{
        //    for(int i = 0; i < arraySize; i++)
        //        std::cout << inpArray[i] << " ";
        //    std::cout << std::endl;
        //}

};

#endif


