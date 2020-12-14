#pragma once

#include "Optional.hpp"
#include "../Exception.hpp"

template <class T>

class DynamicArray {
private:
    Optional<T>* items;
    int size;

public:
    DynamicArray(const T* items, const int size) {
        if (size < 1) {
            throw new Exception;
        }

        this->items = static_cast<Optional<T>*>(operator new [](size * sizeof(Optional<T>)));
        this->size = size;

        for (int i = 0; i < size; i++) {
            this->items[i] = items[i];
        }
    }

    DynamicArray(const int size) {
        if (size < 1) {
            throw new Exception;
        }

        this->items = static_cast<Optional<T>*>(operator new[](size * sizeof(Optional<T>)));
        this->size = size;

        for (int i = 0; i < size; i++) {
            this->items[i] = *Optional<T>::Empty();
        }
    }

    DynamicArray(const DynamicArray<T> &array) {
        (*this) = array;
    }

public:
    int Size() const { return this->size; }

    T Get(const int index) const {
        if (index < 0 ||
            index >= this->Size() ||
            !this->items[index].HasValue()) {
            throw new Exception("Empty value");
        }

        return this->items[index].GetValue();
    }

public:
    void Set(int index, T value) {
        if (index < 0 || index >= this->Size()) {
            throw new Exception;
        }

        this->items[index] = value;
    }

    void Resize(int newSize) {
        if (newSize < 1) {
            throw new Exception;
        }

        if (newSize == this->Size()) {
            return;
        }

        Optional<T>* newArr = static_cast<Optional<T>*>(operator new[](newSize * sizeof(Optional<T>)));

        if (newSize < this->Size()) {
            for (int i = 0; i < newSize; i++) {
                newArr[i] = this->items[i];
            }
        } else {
            int i = 0;

            for (; i < this->Size(); i++) {
                newArr[i] = this->items[i];
            }

            for (; i < newSize; i++) {
                newArr[i] = *(new Optional<T>());
            }
        }

        this->size = newSize;
        this->items = newArr;
    }
};

