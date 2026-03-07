#include "../include/ingest_queue.h"
using namespace std;

IngestQueue::IngestQueue(size_t capacity) {
    buffer = new Post*[capacity];
    this->capacity = capacity;
    head_idx =0;
    tail_idx = 0;
    count = 0;

    for (size_t i =0; i < capacity; i++)
    {
        buffer[i] = nullptr;
    }
}

IngestQueue::~IngestQueue() {
    delete [] buffer;
}

bool IngestQueue::enqueue(Post* p) {
    if (count == capacity)return false;

    buffer[tail_idx] = p;
    tail_idx++;
    if (tail_idx % capacity == 0) tail_idx = 0;
    count++;
    return true;
}

Post* IngestQueue::dequeue() {
    if (count == 0) return nullptr;
    Post *p = buffer[head_idx];
    buffer[head_idx] = nullptr;
    head_idx++;
    if (head_idx % capacity == 0) head_idx =0;
    count--;
    return p;
}

size_t IngestQueue::size() const {
    return count;
}

bool IngestQueue::empty() const {
    if (count == 0) return true;
    return false;   
}

size_t IngestQueue::dequeueBatch(Post** out_array, size_t max_k) {
    if (count == 0) return 0;
    int index = 0;
    if (count < max_k)
    {
        while (count != 0)
        {
            out_array[index] = dequeue();
            index++;
        }
        return index;
    }
    while (index != max_k)
    {
        out_array[index] = dequeue();
        index++;
    }
    return index;
}