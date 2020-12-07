#pragma once

#include "./array/ArraySequence.hpp"
#include "Exception.hpp"

template <class T>
class BinaryTree{
private:
    Sequence<T>* data;

public:
    BinaryTree();
    ~BinaryTree();

    int GetCount();
    int GetCapacity();

    T Get(const T& value);
    bool Contains(const T& value);
    void Add(const T& value);
    void Remove(const T& value);
};

template<class T>
BinaryTree<T>::BinaryTree() {
    data = new ArraySequence<T>();
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    delete data;
}

template<class T>
int BinaryTree<T>::GetCount() {
    int count = 0;

    int capacity = this->GetCapacity();
    for(int i = 0; i < capacity; i++) {
        if (data->Get(i)) {
            count++;
        }
    }

    return count;
}

template<class T>
int BinaryTree<T>::GetCapacity() {
    return data->GetLength();
}

