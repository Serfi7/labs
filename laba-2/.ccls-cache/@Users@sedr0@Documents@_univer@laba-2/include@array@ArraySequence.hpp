#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "../Sequence.hpp"
#include "DynamicArray.hpp"
#include "../Exception.hpp"

template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* items;
    int length;

public:
    ArraySequence(T* items, int size) {
        this->items = new DynamicArray<T>(items, size);
        this->length = size;
    }

    ArraySequence(const int size = 0) : length(0) {
        this->items = new DynamicArray<T>(size > 0 ? size : 1);
    }

    ArraySequence(const DynamicArray<T> *array) {
        this->items = new DynamicArray<T>(*array);
        this->length = array->Size();
    }

    ArraySequence(const Sequence<T> &sequence) {
        const ArraySequence<T>* array = static_cast<const ArraySequence<T>*>(&sequence);

        if (array) {
            this->items = new DynamicArray<T>(*array->items);
            this->length = array->length;

            return;
        }

        int seqLength = sequence.GetLength();
        DynamicArray<T>* copiedArr = new DynamicArray<T>(seqLength);

        for (int i = 0; i < seqLength; i++) {
            copiedArr->Set(i, sequence.Get(i));
        }

        this->items = copiedArr;
        this->length = seqLength;
    }

public:
    virtual T GetFirst() const override {
        return this->items->Get(0);
    }

    virtual T GetLast() const override {
        return this->items->Get(this->GetLength() - 1);
    }

    virtual T Get(int index) const override{
        return this->items->Get(index);
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        int subLength = endIndex - startIndex;

        ArraySequence<T>* subsequence = new ArraySequence<T>(subLength);
        subsequence->length = subLength;

        for (int i = 0; i < subLength; i++) {
            subsequence->items->Set(i, this->items->Get(startIndex + i));
        }

        return subsequence;
    }

    virtual int GetLength() const override {
        return this->length;
    }

    virtual int GetCapacity() const override {
        return this->items->Size();
    }

public:
    virtual void Append(T item) override {
        if (this->GetLength() == this->items->Size()) {
            this->items->Resize(2 * this->length);
        }

        this->items->Set(this->length++, item);
    }

    virtual void Prepend(T item) override {
        return InsertAt(item, 0);
    }

    virtual void InsertAt(T item, const int index) override {
        if (index < 0 || index > this->GetLength()) {
            throw new Exception;
        }

        if (index == this->GetLength()) {
            return Append(item);
        }

        if (this->GetLength() == this->items->Size()) {
            this->items->Resize(this->GetLength() + 1);
        }

        this->length++;

        for (int i = this->GetLength() - 1; i > index; i--) {
            this->items->Set(i, this->items->Get(i - 1));
        }

        this->items->Set(index, item);
    }

    virtual void Set(const T& value, const int index) override {
        this->items->Set(index, value);
    }

    virtual void RemoveAt(const int index) override {
        if (index < 0 || index >= this->GetLength()) {
            throw new Exception;
        }

        for (int i = index; i < this->GetLength() - 1; i++) {
            this->items->Set(i, this->items->Get(i + 1));
        }

        this->length--;
    }

    virtual void Remove(T value) override {
        for (int i = 0; i < this->GetLength(); i++) {
            if (value == this->items->Get(i)) {
                return this->RemoveAt(i);
            }
        }
    }

    void Remove(int (*cmp)(const T&)) {
        int i = 0;
        int j = 0;

        int length = this->GetLength();

        if (!length) {
            return;
        }

        for (; i < length; i++) {
            T current = this->Get(i);

            if (cmp(current) == 0) {
                if (i == j) {
                    j++;
                    continue;
                }

                T temp = Get(j);
                Set(current, j);
                Set(temp, i);
                j++;
            }
        }

        items->Resize(j);
        this->length = j;
    }

    virtual void RemoveAll(T value) override {
        for (int i = 0; i < this->GetLength(); i++) {
            if (value == this->items->Get(i)) {
                this->RemoveAt(i);
            }
        }
    }

    virtual Sequence<T>* Concat(Sequence <T> *list) override {
        ArraySequence<T>* concatedSequence = new ArraySequence<T>(*(Sequence<T>*)this);

        int newLength = concatedSequence->GetLength() + list->GetLength();
        concatedSequence->items->Resize(newLength);

        for (int i = 0; i < list->GetLength(); i++) {
            concatedSequence->Append(list->Get(i));
        }

        return concatedSequence;
    }

    virtual Sequence<T>* Copy() override {
        return new ArraySequence<T>(*(Sequence<T>*)this);
    }

    virtual Sequence<T>* CopyTo(Sequence <T>* target, const int startIndex) override {
        int thisLength = this->GetLength();
        int targetLength = target->GetLength();

        if (targetLength <= thisLength + startIndex) {
            int i = 0;
            for (; i + startIndex < targetLength; i++) {
                target->RemoveAt(i + startIndex);
                target->InsertAt(this->Get(i), i + startIndex);
            }

            for (; i < thisLength; i++) {
                target->Append(this->Get(i));
            }

            return target;
        }

        for (int i = 0; i < thisLength; i++) {
            target->RemoveAt(i + startIndex);
            target->InsertAt(this->Get(i), i + startIndex);
        }

        return target;
    }
};

