#pragma once

#include <iostream>

#include "../include/ISorter.hpp"
#include "../include/Sorter.hpp"

#include "../include/array/ArraySequence.hpp"

#include "../include/list/LinkedListSequence.hpp"

#include "Mock.hpp"

using namespace std;
using namespace Mock;

class SorterTest {
public:
    SorterTest() {
        TestArrayShakerSort();
        TestLinkedListShakerSort();

        TestArrayQuickSort();
        TestLinkedListQuickSort();
    }

private:
    void TestArrayShakerSort() {
        cout << "    Shaker sorting ArraySequence<int>" << endl;

        Sequence<int>* mockIntArraySequence = new ArraySequence<int>(mockIntArray, mockArrayLength);

        bool isError = false;

        ISorter<int>* sorter = new Sorter<int>();

        Sequence<int>* sortedArray = sorter->ShakerSort(
            mockIntArraySequence,
            [](int a, int b) -> int {
                return a - b;
            }
        );

        for (int i = 0; i < mockArrayLength; i++) {
            if (sortedArray->Get(i) == mockSortedIntArray[i]) {
                continue;
            }

            isError = true;
            break;
        }

        mockIntArraySequence->Set(33, 0);

        bool isMutate = false;
        if (mockIntArraySequence->Get(0) == sortedArray->Get(0)) {
            isError = true;
            isMutate = true;
        }

        if (isError) {
            cout << "        ERROR Shaker sort worked wrong. Array: ";

            for (int i = 0; i < mockArrayLength; i++) {
                cout << sortedArray->Get(i) << " ";
            }

            if (isMutate) {
                cout << ". Source array was changed" << endl;
            }

            cout << endl;
        } else {
            cout << "        SUCCESS Shaker sort worked successfully" << endl;
        }
    }

    void TestLinkedListShakerSort() {
        cout << "    Shaker sorting LinkedListSequence<char>" << endl;

        Sequence<char>* mockCharLinkedListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;

        ISorter<char>* sorter = new Sorter<char>();

        Sequence<char>* sortedArray = sorter->ShakerSort(
            mockCharLinkedListSequence,
            [](char a, char b) -> int {
                return a > b;
            }
        );

        for (int i = 0; i < mockArrayLength; i++) {
            if (sortedArray->Get(i) == mockSortedCharArray[i]) {
                continue;
            }

            isError = true;
            break;
        }

        mockCharLinkedListSequence->Set('a', 0);

        bool isMutate = false;
        if (mockCharLinkedListSequence->Get(0) == sortedArray->Get(0)) {
            isError = true;
            isMutate = true;
        }

        if (isError) {
            cout << "        ERROR Shaker sort worked wrong. Array: ";

            for (int i = 0; i < mockArrayLength; i++) {
                cout << sortedArray->Get(i) << " ";
            }

            if (isMutate) {
                cout << ". Source array was changed" << endl;
            }

            cout << endl;
        } else {
            cout << "        SUCCESS Shaker sort worked successfully" << endl;
        }
    }

    void TestArrayQuickSort() {
        cout << "    Quick sorting ArraySequence<int>" << endl;

        Sequence<int>* mockIntArraySequence = new ArraySequence<int>(mockIntArray, mockArrayLength);

        bool isError = false;

        ISorter<int>* sorter = new Sorter<int>();

        Sequence<int>* sortedArray = sorter->QuickSort(
            mockIntArraySequence,
            [](int a, int b) -> int {
                return a - b;
            }
        );

        for (int i = 0; i < mockArrayLength; i++) {
            if (sortedArray->Get(i) == mockSortedIntArray[i]) {
                continue;
            }

            isError = true;
            break;
        }

        mockIntArraySequence->Set(33, 0);

        bool isMutate = false;
        if (mockIntArraySequence->Get(0) == sortedArray->Get(0)) {
            isError = true;
            isMutate = true;
        }

        if (isError) {
            cout << "        ERROR Quick sort worked wrong. Array: ";

            for (int i = 0; i < mockArrayLength; i++) {
                cout << sortedArray->Get(i) << " ";
            }

            if (isMutate) {
                cout << ". Source array was changed" << endl;
            }

            cout << endl;
        } else {
            cout << "        SUCCESS Quick sort worked successfully" << endl;
        }
    }

    void TestLinkedListQuickSort() {
        cout << "    Quick sorting LinkedListSequence<char>" << endl;

        Sequence<char>* mockCharLinkedListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;

        ISorter<char>* sorter = new Sorter<char>();

        Sequence<char>* sortedArray = sorter->QuickSort(
            mockCharLinkedListSequence,
            [](char a, char b) -> int {
                return a > b;
            }
        );

        for (int i = 0; i < mockArrayLength; i++) {
            if (sortedArray->Get(i) == mockSortedCharArray[i]) {
                continue;
            }

            isError = true;
            break;
        }

        mockCharLinkedListSequence->Set('a', 0);

        bool isMutate = false;
        if (mockCharLinkedListSequence->Get(0) == sortedArray->Get(0)) {
            isError = true;
            isMutate = true;
        }

        if (isError) {
            cout << "        ERROR Quick sort worked wrong. Array: ";

            for (int i = 0; i < mockArrayLength; i++) {
                cout << sortedArray->Get(i) << " ";
            }

            if (isMutate) {
                cout << ". Source array was changed" << endl;
            }

            cout << endl;
        } else {
            cout << "        SUCCESS Quick sort worked successfully" << endl;
        }
    }
};

