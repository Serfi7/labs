#pragma once

#include "iostream"

#include "ISorter.hpp"

template<class T>
class Sorter : public ISorter<T> {
    virtual Sequence<T>* ShakerSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        Sequence<T>* copySeq = seq->Copy();

        int count = copySeq->GetLength();
        int left = 0;
        int right = count - 1;
        int flag = 1;

        while (left < right && flag > 0) {
            flag = 0;

            for (int i = left; i < right; i++) {
                T current = copySeq->Get(i);
                T next = copySeq->Get(i + 1);

                if(cmp(current, next) > 0) {
                    copySeq->Set(next, i);
                    copySeq->Set(current, i + 1);
                    flag = 1;
                }
            }

            right--;
            for (int i = right; i > left; i--) {
                T prev = copySeq->Get(i - 1);
                T current = copySeq->Get(i);

                if (cmp(prev, current) > 0) {
                    copySeq->Set(prev, i);
                    copySeq->Set(current, i - 1);
                    flag = 1;
                }
            }
            left++;
        }

        return copySeq;
    }

    virtual Sequence<T>* QuickSort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        Sequence<T>* copySeq = seq->Copy();

        return QuickSort(copySeq, 0, copySeq->GetLength() - 1, cmp);
    }

private:
    int Partition(Sequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        T pivot = seq->Get(right);
        int leftIndex = left;

        for (int u = left; u <= right - 1; u++) {
            T current = seq->Get(u);

            if (cmp(current, pivot) <= 0) {
                T smaller = seq->Get(leftIndex);

                seq->Set(smaller, u);
                seq->Set(current, leftIndex);

                leftIndex++;
            }
        }

        T smaller = seq->Get(leftIndex);

        seq->Set(smaller, right);
        seq->Set(pivot, leftIndex);
        return leftIndex;
    }

    Sequence<T>* QuickSort(Sequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) {
            return seq;
        }

        int pivotIndex = Partition(seq, left, right, cmp);

        QuickSort(seq, left, pivotIndex - 1, cmp);
        QuickSort(seq, pivotIndex + 1, right, cmp);

        return seq;
    }
};

