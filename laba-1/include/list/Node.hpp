#pragma once

#include "../Exception.hpp"

template<class T>
class Node {
public:
    Node<T>(T& value) {
        this->value = static_cast<T*>(operator new[](sizeof(T)));

        *this->value = value;
        this->next = NULL;
    }

    T* value;
    Node<T>* next;
};
