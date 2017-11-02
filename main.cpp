#include <iostream>
#include <cmath>
#include "CircularBuffer.h"

int main() {
    std::srand(time(NULL));
    int value;
    int pushCount = 0;
    int popCount = 0;


    CircularBuffer<int> buffer;
    for (int i = 0; i < 10000; i++){
        if (buffer.isEmpty()) {
            value = rand();
            buffer.push(value);
            std::cout << buffer.size() << "\t" << "push\t\t" << value << std::endl;
            pushCount++;
        } else if (buffer.isFull()) {
            value = buffer.pop();
            std::cout << buffer.size() << "\t" << "pop\t\t\t\t\t\t\t\t" << value << std::endl;
            popCount++;
        } else {
            value = rand();
            if (value % 3 > 0) {
                buffer.push(value);
                std::cout << buffer.size() << "\t" << "push\t\t" << value << std::endl;
                pushCount++;
            } else {
                value = buffer.pop();
                std::cout << buffer.size() << "\t" << "pop\t\t\t\t\t\t\t\t" << value << std::endl;
                popCount++;
            }
        }
    }

    std::cout << std::endl;
    std::cout << buffer.size() << " = " << pushCount << " - " << popCount << std::endl;
    std::cout << std::endl;

    while (!buffer.isFull()) {
        value = rand();
        buffer.push(value);
        std::cout << buffer.size() << "\t" << "push\t\t" << value << std::endl;
    }

    CircularBuffer<int> bufferCopy(buffer);

    std::cout << std::endl;

    while (!buffer.isEmpty()) {
        value = buffer.pop();
        std::cout << buffer.size() << "\t" << "pop\t\t\t\t\t\t\t\t" << value << std::endl;
    }

    while (!bufferCopy.isEmpty()) {
        value = bufferCopy.pop();
        std::cout << bufferCopy.size() << "\t" << "pop\t\t\t\t\t\t\t\t" << value << std::endl;
    }

    std::cout << std::endl;

    while (!buffer.isFull()) {
        value = rand();
        buffer.push(value);
        std::cout << buffer.size() << "\t" << "push\t\t" << value << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "buffer size:" <<buffer.size() << " (buffer tail: " << buffer.peek() << ")" << std::endl;
    CircularBuffer<int> moveBuffer = std::move(buffer);
    std::cout << "buffer size after move:" << buffer.size() << std::endl;
    std::cout << "move buffer size:" << moveBuffer.size() << " (buffer tail: " << moveBuffer.peek() << ")" << std::endl;

    std::string words [3] = {"ready", "set", "go!"};

    CircularBuffer<std::string> *stringBuffer = new CircularBuffer<std::string>(20, words, 3);

    while (!stringBuffer->isEmpty()) {
        std::cout << stringBuffer->pop() << std::endl;
    }

    while (!buffer.isFull()) {
        buffer.push(rand());
    }

    std::cout << "is buffer full: " << buffer.isFull() << " (" << buffer.size() << ")" << std::endl;
    buffer.clear();
    std::cout << "is buffer full: " << buffer.isFull() << " (" << buffer.size() << ")" << std::endl;
    
    return 0;
}