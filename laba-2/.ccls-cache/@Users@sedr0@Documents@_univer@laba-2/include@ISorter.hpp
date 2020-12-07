#pragma once

#include "Sequence.hpp"

template <class T>
class ISorter {
public:
    virtual Sequence<T>* ShakerSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
    virtual Sequence<T>* QuickSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) = 0;
};

