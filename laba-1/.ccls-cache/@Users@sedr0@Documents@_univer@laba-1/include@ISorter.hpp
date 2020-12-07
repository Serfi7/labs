#pragma once

#include "Sequence.hpp"
#include "./list/LinkedListSequence.hpp"

template <class T>
class ISorter {
public:
    virtual Sequence<T>* ShakerSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
    virtual Sequence<T>* QuickSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
    virtual Sequence<T>* LinkedListSort(LinkedListSequence<T>* list, int (*cmp)(const T&, const T&)) = 0;
};

