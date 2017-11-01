#include <stdexcept>
#include <string.h>
#include "CircularBuffer.h"

template <class T> CircularBuffer<T>::CircularBuffer(): maxSize(DEFAULT_CAPACITY), head(0), tail(0), isBufferFull(false) {
    circularBuffer = new T[maxSize];
}

template <class T> CircularBuffer<T>::CircularBuffer(unsigned int bufferCapacity): maxSize(bufferCapacity), head(0), tail(0), isBufferFull(bufferCapacity == 0) {
    circularBuffer = new T[maxSize];
}

template <class T> CircularBuffer<T>::CircularBuffer(unsigned int bufferCapacity, T *initialContent, unsigned int initialSize){
    if(initialSize >= bufferCapacity) {
        throw std::invalid_argument("Initial size must not be greater than buffer capacity");
    }
    maxSize = bufferCapacity;
    head = initialSize;
    isBufferFull = bufferCapacity == initialSize;
    circularBuffer = new T[maxSize];
    memcpy(circularBuffer, initialContent, initialSize * sizeof(T));
}

template <class T> CircularBuffer<T>::CircularBuffer(CircularBuffer<T> &anotherBuffer) {
    maxSize = anotherBuffer.maxSize;
    head = anotherBuffer.head;
    tail = anotherBuffer.tail;
    isBufferFull = anotherBuffer.isBufferFull;
    circularBuffer = new T[maxSize];
    memcpy(circularBuffer, anotherBuffer.circularBuffer, maxSize * sizeof(T));
}

template <class T> CircularBuffer<T>::CircularBuffer(CircularBuffer<T> &&anotherBuffer) {
    maxSize = anotherBuffer.maxSize;
    head = anotherBuffer.head;
    tail = anotherBuffer.tail;
    isBufferFull = anotherBuffer.isBufferFull;
    circularBuffer = new T[maxSize];
    memmove(circularBuffer, anotherBuffer.circularBuffer, maxSize * sizeof(T));

    anotherBuffer.maxSize = DEFAULT_CAPACITY;
    anotherBuffer.head = 0;
    anotherBuffer.tail = 0;
    anotherBuffer.isBufferFull = false;
    anotherBuffer.circularBuffer = new T[anotherBuffer.maxSize];
}

template <class T> CircularBuffer<T>::~CircularBuffer() {
    delete circularBuffer;
}

template <class T> void CircularBuffer<T>::push(T element) {
    if (!isBufferFull) {
        circularBuffer[head] = element;
        head = (head + 1) % maxSize;
        isBufferFull = head == tail;
    } else {
        throw std::overflow_error("Cannot push to full buffer!");
    }
}

template <class T> T CircularBuffer<T>::pop() {
    if (head == tail && !isBufferFull) {
        throw std::underflow_error("Cannot pop from empty buffer!");
    } else {
        T result = circularBuffer[tail];
        tail = (tail + 1) % maxSize;
        if (isBufferFull) {
            isBufferFull = !isBufferFull;
        }
        return result;
    }
}

template <class T> T CircularBuffer<T>::peek() {
    if (head == tail && !isBufferFull) {
        throw std::underflow_error("Cannot peek from empty buffer!");
    } else {
        return circularBuffer[tail];
    }
}

template <class T> unsigned int CircularBuffer<T>::size() {
    return isBufferFull ? maxSize : (head >= tail ? head - tail : head + maxSize - tail);
}