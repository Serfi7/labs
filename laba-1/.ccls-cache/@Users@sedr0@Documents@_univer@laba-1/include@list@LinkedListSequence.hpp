#pragma once

#include <iostream>

#include "../Sequence.hpp"
#include "LinkedList.hpp"
#include "../Exception.hpp"

template<class T>
class LinkedListSequence : public Sequence<T> {
private:
    LinkedList<T>* items;

public:
    LinkedListSequence(T* items, const int size) {
        this->items = new LinkedList<T>(items, size >= 0 ? size : 0);
    }

    LinkedListSequence() {
        this->items = new LinkedList<T>();
    }

    LinkedListSequence(const LinkedList<T> *list) {
        this->items = new LinkedList<T>(*list);
    }

    LinkedListSequence(const Sequence<T> &sequence) {
        const LinkedListSequence<T>* list = static_cast<const LinkedListSequence<T>*>(&sequence);

        if (list) {
            this->items = new LinkedList<T>(*list->items);

            return;
        }

        int seqLength = sequence.GetLength();
        LinkedList<T>* copiedList = new LinkedList<T>();

        for (int i = 0; i < seqLength; i++) {
            copiedList->Append(sequence.Get(i));
        }

        this->items = copiedList;
    }

public:
    void SetHead(Node<T>* head) {
        items->SetHead(head);
    }

    void SetTail(Node<T>* tail) {
        items->SetTail(tail);
    }

    Node<T>* Head() const {
        return items->Head();
    }

    Node<T>* Tail() const {
        return items->Tail();
    }

    virtual T GetFirst() const override {
        return this->items->GetFirst();
    }

    virtual T GetLast() const override {
        return this->items->GetLast();
    }

    virtual T Get(int index) const override{
        return this->items->Get(index);
    }

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        LinkedListSequence<T>* subsequence = new LinkedListSequence<T>();

        subsequence->items = this->items->GetSubList(startIndex, endIndex);

        return subsequence;
    }

    virtual int GetLength() const override {
        return this->items->GetLength();
    }

public:
    virtual void Prepend(T item) override {
        this->items->Prepend(item);
    }

    virtual void Append(T item) override {
        this->items->Append(item);
    }

    virtual void InsertAt(T item, const int index) override {
        this->items->InsertAt(item, index);
    }

    virtual void Set(T item, const int index) override {
        this->items->Set(item, index);
    }

    virtual void RemoveAt(const int index) override {
        this->items->RemoveAt(index);
    }

    virtual void Remove(T value) override {
        this->items->Remove(value);
    }

    virtual void RemoveAll(T value) override {
        this->items->RemoveAll(value);
    }

    virtual Sequence<T>* Concat(Sequence <T> *sequence) override {
        LinkedListSequence<T>* concatedSequence = new LinkedListSequence<T>(*this);
        LinkedListSequence<T>* castedList = dynamic_cast<LinkedListSequence<T>*>(sequence);

        try {
            std::cout << "if casted" << std::endl;
            concatedSequence->items = concatedSequence->items->Concat(castedList->items);
        } catch(...) {
            int listLength = sequence->GetLength();

            for (int i = 0; i < listLength; i++) {
                concatedSequence->Append(sequence->Get(i));
            }
        }

        return concatedSequence;
    }

    virtual Sequence<T>* Copy() override {
        return new LinkedListSequence<T>(*(Sequence<T>*)this);
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
