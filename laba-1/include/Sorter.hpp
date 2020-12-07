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

    virtual Sequence<T>* LinkedListSort(LinkedListSequence<T>* list, int (*cmp)(const T&, const T&)) override {
        Node<T>* head = list->Head();

        if (!head || !head->next) {
            return list;
        }

        Node<T>* newHead = MergeListSort(&head, cmp);
        Node<T>* newTail = newHead;

        while (newTail->next) {
            newTail = newTail->next;
        }

        list->SetHead(newHead);
        list->SetTail(newTail);

        return list;
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

    Node<T>* MergeListSort(Node<T>** ptr_head, int (*cmp)(const T&, const T&)) {
        Node<T>* head = *ptr_head;
        Node<T>* leftPart;
        Node<T>* rightPart;

        if (!head) {
            return NULL;
        }

        if (!head->next) {
            return head;
        }

        SplitList(head, &leftPart, &rightPart);
        //std::cout << "after split" << std::endl;
        //std::cout << *leftPart->value << " " << *rightPart->value << std::endl;

        leftPart = MergeListSort(&leftPart, cmp);
        rightPart = MergeListSort(&rightPart, cmp);

        Node<T>* newHead = MergeSortedLists(leftPart, rightPart, cmp);
        return newHead;
    }

    void SplitList(Node<T>* source, Node<T>** leftPart, Node<T>** rightPart) {
        Node<T>* node1 = source->next;
        Node<T>* node2 = source;

        while (node1 != NULL) {
            node1 = node1->next;

            if (node1 != NULL) {
                node1 = node1->next;
                node2 = node2->next;
            }
        }

        *leftPart = source;
        *rightPart = node2->next;
        node2->next = NULL;
    }

    Node<T>* MergeSortedLists(Node<T>* list1, Node<T>* list2, int (*cmp)(const T&,const T&)) {
        Node<T>* result = NULL;

        if (!list1) {
            return list2;
        }

        if (!list2) {
            return list1;
        }

        if (cmp(*list1->value, *list2->value) <= 0) {
            result = list1;
            result->next = MergeSortedLists(list1->next, list2, cmp);
        } else {
            result = list2;
            result-> next = MergeSortedLists(list1, list2->next, cmp);
        }

        return result;
    }
};

