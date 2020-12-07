#pragma once

#include "./array/ArraySequence.hpp"
#include "Exception.hpp"

template <class T>
class BinarySearchTree{
private:
    Sequence<T>* data;

    int _rootIndex();
    int _leftChildIndex(const int parentIndex);
    int _rightChildIndex(const int parentIndex);
    T _leftChild(const int parentIndex);
    T _rightChild(const int parentIndex);

    T _get(const T& value, const int rootIndex);
    T _getMinElement(const int rootIndex);

    int _insertionIndex(const T& value, const int rootIndex);

    void _remove(const T& value, const int rootIndex);
    void _moveUpRightChildren(const int rootIndex);
    void _moveUpLeftChildren(const int rootIndex);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    int GetCount();
    int GetCapacity();

    T& Get(const T& value);
    bool Contains(const T& value);
    void Add(const T& value);
    void Remove(const T& value);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    data = new ArraySequence<T>();
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    delete data;
}

template<class T>
int BinarySearchTree<T>::_rootIndex() {
    return 0;
}

template<class T>
int BinarySearchTree<T>::GetCount() {
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
int BinarySearchTree<T>::GetCapacity() {
    return data->GetLength();
}

template<class T>
int BinarySearchTree<T>::_leftChildIndex(const int parentIndex) {
    return parentIndex * 2 + 1;
}

template<class T>
int BinarySearchTree<T>::_rightChildIndex(const int parentIndex) {
    return parentIndex * 2 + 2;
}

template<class T>
T BinarySearchTree<T>::_leftChild(const int parentIndex) {
    return data->Get(_leftChildIndex(parentIndex));
}

template<class T>
T BinarySearchTree<T>::_rightChild(const int parentIndex) {
    return data->Get(_rightChildIndex(parentIndex));
}

template<class T>
T BinarySearchTree<T>::_get(const T& value, const int rootIndex) {
    T& root = data->Get(rootIndex);

    if (!root) {
        return NULL;
    }

    if (value < root) {
        return _get(value, _leftChildIndex(rootIndex));
    }

    if (value > root) {
        return _get(value, _rightChildIndex(rootIndex));
    }

    return root;
}

template<class T>
T BinarySearchTree<T>::_getMinElement(const int parentIndex) {
    T& leftChild = _leftChild(parentIndex);

    if (leftChild) {
        return leftChild;
    }

    return data->Get(parentIndex);
}

template<class T>
int BinarySearchTree<T>::_insertionIndex(const T& value, const int rootIndex) {
    T& root = data->Get(rootIndex);

    if (!root) {
        return rootIndex;
    }

    if (value < rootIndex) {
        return _insertionIndex(value, _leftChildIndex(rootIndex));
    }

    if (value > rootIndex) {
        return _insertionIndex(value, _rightChildIndex(rootIndex));
    }

    return rootIndex;
}

template<class T>
void BinarySearchTree<T>::_moveUpRightChildren(const int rootIndex) {
    T& rightChild = _rightChild(rootIndex);

    if (!rightChild) {
        return;
    }

    data->Set(_rightChild(rootIndex), rootIndex);

    _moveUpRightChildren(_rightChildIndex(rootIndex));
}

template<class T>
void BinarySearchTree<T>::_moveUpLeftChildren(const int rootIndex) {
    T& leftChild = _leftChild(rootIndex);

    if (!leftChild) {
        return;
    }

    data->Set(_leftChild(rootIndex), rootIndex);

    _moveUpRightChildren(_leftChildIndex(rootIndex));
}

template<class T>
void BinarySearchTree<T>::_remove(const T& value, const int rootIndex) {
    T& root = data->Get(rootIndex);

    if (!root) {
        throw new Exception("This value is not existed in tree");
    }

    if (value < root) {
        return _remove(value, _leftChildIndex(rootIndex));
    }

    if (value > root) {
        return _remove(value, _rightChildIndex(rootIndex));
    }


    if (!_leftChild(rootIndex)) {
        return _moveUpRightChildren(rootIndex);
    }

    if (!_rightChild(rootIndex)) {
        return _moveUpLeftChildren(rootIndex);
    }

    T& minElement = _getMinElement(rootIndex);

    data->Set(minElement, rootIndex);
    _remove(minElement, _rightChildIndex(rootIndex));
}

template<class T>
T& BinarySearchTree<T>::Get(const T& value) {
    return _get(value, _rootIndex());
}

template<class T>
bool BinarySearchTree<T>::Contains(const T& value) {
    T& element = _get(value, _rootIndex());

    if(element) {
        return true;
    }

    return false;
}

template<class T>
void BinarySearchTree<T>::Add(const T& value) {
    int insertionIndex = _insertionIndex(value, _rootIndex());

    data->Set(value, insertionIndex);
}

template<class T>
void BinarySearchTree<T>::Remove(const T& value) {
    _remove(value, _rootIndex());
}

