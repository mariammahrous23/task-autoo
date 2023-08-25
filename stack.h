#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class Stack {
private:
    struct NodeS {
        T data;
        NodeS* next;
        NodeS(const T& value) : data(value), next(nullptr) {}
    };

    NodeS* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(const T& value) {
        NodeS* newNode = new NodeS(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    NodeS* pop() {
        if (!empty()) {
            NodeS* temp = topNode;
            topNode = topNode->next;
            return temp;
        }
        return nullptr; // Or throw an exception to indicate stack underflow
    }

    T& top() {
        if (!empty()) {
            return topNode->data;
        }
        throw std::runtime_error("Stack is empty!");
    }

    const T& top() const {
        if (!empty()) {
            return topNode->data;
        }
        throw std::runtime_error("Stack is empty!");
    }

    bool empty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        NodeS* current = topNode;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void clear() {
        while (!empty()) {
            NodeS* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    void print() const {
        NodeS* current = topNode;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~Stack() {
        clear();
    }
};

#endif // STACK_H
