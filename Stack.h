#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    T& pop() {
        if (!empty()) {
            data.pop_back();
            return data.back();
        }
    }

    T& peek() {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() {
        data.clear();
    }

};

#endif // STACK_H
