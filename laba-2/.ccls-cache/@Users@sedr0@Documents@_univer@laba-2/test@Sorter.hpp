#pragma once

#include <iostream>

#include "../include/ISorter.hpp"
#include "../include/Sorter.hpp"

#include "../include/array/ArraySequence.hpp"

#include "Mock.hpp"

using namespace std;
using namespace Mock;

class SorterTest {
public:
    SorterTest() {
        TestArrayShakerSort();

        TestArrayQuickSort();
    }

private:
    void TestArrayShakerSort() {
        cout << "    Shaker sorting ArraySequence<int>" << endl;

        Sequence<int>* mockIntArraySequence = new ArraySequence<int>(mockIntArray, mockArrayLength);

        bool isError = false;

        ISorter<int>* sorter = new Sorter<int>();

        Sequence<int>* sortedArray = sorter->ShakerSort(
            mockIntArraySequence,
            [](const int& a, const int& b) -> int {
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

    void TestArrayQuickSort() {
        cout << "    Quick sorting ArraySequence<int>" << endl;

        Sequence<int>* mockIntArraySequence = new ArraySequence<int>(mockIntArray, mockArrayLength);

        bool isError = false;

        ISorter<int>* sorter = new Sorter<int>();

        Sequence<int>* sortedArray = sorter->QuickSort(
            mockIntArraySequence,
            [](const int& a, const int& b) -> int {
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
};

