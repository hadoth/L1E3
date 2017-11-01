#ifndef L1E3_CIRCULARBUFFER_H
#define L1E3_CIRCULARBUFFER_H

unsigned int DEFAULT_CAPACITY = 128;

template <class T> class CircularBuffer {
private:
    T *circularBuffer;
    unsigned int head;
    unsigned int tail;
    unsigned int maxSize;
    bool isBufferFull;
public:
    CircularBuffer();
    CircularBuffer(unsigned int bufferCapacity);
    CircularBuffer(unsigned int bufferCapacity, T *initialContent, unsigned int initialSize);
    CircularBuffer(CircularBuffer<T> &anotherBuffer);
    CircularBuffer(CircularBuffer<T> &&anotherBuffer);
    ~CircularBuffer();
    void push(T element);
    T pop();
    T peek();
    inline const bool isEmpty() {return head == tail && !isBufferFull;};
    inline const bool isFull() {return isBufferFull;};
    inline const void clear() {head = 0; tail = 0, isBufferFull = false;};
    unsigned int size();
};

#include "CircularBuffer.cpp" // as suggested in https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp

#endif //L1E3_CIRCULARBUFFER_H
