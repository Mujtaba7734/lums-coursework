#include "Heap.h"
#include <iostream>
#include <climits> 

using namespace std;

MinHeap::MinHeap(int cap)
{
    this->heap_size = 0;
    this->capacity = cap;
    if (this->capacity <= 0 )
    {
        harr = nullptr;
        this->capacity = 0;
    }
    else
    {
        harr = new int[cap];    
    }
}

MinHeap::~MinHeap()
{
    if (harr != nullptr)
    {
        delete [] harr;
        harr = nullptr;
    }
}

MinHeap::MinHeap(const MinHeap& other)
{
    this->capacity = other.capacity;
    this->heap_size = other.heap_size;
    
    if (!other.harr && capacity <= 0)
    {
        harr = nullptr;
        this->capacity = 0;
    }
    else
    {
        this->harr = new int[capacity];
        for (int i = 0; i < heap_size; i++)
        {
            harr[i] = other.harr[i];
        }
    }
}

MinHeap& MinHeap::operator=(const MinHeap& other)
{
    if (this == &other) return *this;
    if (harr)
    {
        delete[] harr;
        harr = nullptr;
    }
    capacity = other.capacity;
    heap_size = other.heap_size;

    if (!other.harr && capacity <= 0)
    {
        harr = nullptr;
        this->capacity = 0;
    }
    else
    {
        this->harr = new int[capacity];
        for (int i = 0; i < heap_size; i++)
        {
            this->harr[i] = other.harr[i];
        } 
    }
    return *this;
}

int MinHeap::extractMin()
{
    if (!harr) return INT_MAX;
    if (heap_size <= 0) return INT_MAX;
    
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }

    int min = harr[0];
    harr[0] = harr[heap_size -1];
    heap_size--;

    minHeapify(0);
    return min;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if (!harr) return;;
    if (i < 0) return;
    if (i >= heap_size) return;
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::increaseKey(int i, int new_val)
{
    if (!harr) return;;
    if (i < 0) return;
    if (i >= heap_size) return;
    harr[i] = new_val;
    minHeapify(i);
}

int MinHeap::getMin() const
{
    if (!harr) return INT_MAX;
    if (heap_size <=0) return INT_MAX;
    return harr[0];
}

void MinHeap::deleteKey(int i)
{
    if (!harr) return;
    if (i < 0) return;
    if (i >= heap_size) return;

    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        int new_capacity = 0;
        if (capacity == 0) new_capacity = 1;
        else new_capacity = capacity *2;
        
        int *new_harr = new int[new_capacity];
        for (int i = 0; i < heap_size; i++)
        {
            new_harr[i] = harr[i];
        } 
        if (harr) delete[] harr;        
        harr = new_harr;
        capacity = new_capacity;
    }

    int i = heap_size;
    heap_size++;
    harr[i] = k;
    while (i != 0 && harr[parent(i)] > harr[i])
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::minHeapify(int i)
{
    if (!harr) return;
    if (i < 0) return;
    if (i >= heap_size) return;

    int l = left(i);
    int r =right(i);
    int smallest = i;

    if (l < heap_size && harr[l] < harr[smallest]) smallest = l;
    if (r < heap_size && harr[r] < harr[smallest]) smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        minHeapify(smallest);
    }
}