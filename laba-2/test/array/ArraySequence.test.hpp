#pragma once

#include "iostream"

#include "../../include/array/ArraySequence.hpp"
#include "../Mock.hpp"

using namespace std;
using namespace Mock;

class ArraySequenceTest {
public:
    ArraySequenceTest() {
        TestCtorWithArray();
        cout << endl;
        TestCtorWithSize();
        cout << endl;
        TestCtorWithDynamicArray();
        cout << endl;
        TestCopingCtor();
        cout << endl;

        TestGetFirst();
        cout << endl;
        TestGetLast();
        cout << endl;
        TestGetSubsequence();
        cout << endl;
        TestGetLength();
        cout << endl;

        TestPrepend();
        cout << endl;
        TestAppend();
        cout << endl;
        TestRemoveAt();
        cout << endl;
        TestRemove();
        cout << endl;
        TestRemoveAll();
        cout << endl;
        TestConcat();
        cout << endl;
        TestCopy();
        cout << endl;
        TestCopyTo();
    }

private:
    void TestCtorWithArray() {
        cout << "    Creating ArraySequence<char> by source char array" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        for (int i = 0; i < mockArrayLength; i++) {
            char mockValue = mockCharArray[i];
            char arraySequenceValue = mockCharArraySequence->Get(i);

            if (mockValue != arraySequenceValue) {
                cout << "        ERROR Char elements at " << i << " is not equal (source " << mockValue << ", DynArray " << arraySequenceValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<char> was successful created by mock array" << endl;
        }

        cout << "    Creating ArraySequence<char> by source char array with zero and less length" << endl;

        try {
            mockCharArraySequence = new ArraySequence<char>(mockCharArray, 0);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS ArraySequence<char> with zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR ArraySequence<char> with zero length was created" << endl;
        }

        try {
            mockCharArraySequence = new ArraySequence<char>(mockCharArray, -1);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS ArraySequence<char> with less zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR ArraySequence<char> with less zero length was created" << endl;
        }

        cout << "    Creating ArraySequence<Object> by source char array" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();

        Sequence<MockClass>* mockObjectArraySequence = new ArraySequence<MockClass>(mockObjectArray, 3);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass arraySequenceValue = mockObjectArraySequence->Get(i);

            if (mockValue != arraySequenceValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, DynArray: {str:  " << arraySequenceValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<Object> was successful created by mock array" << endl;
        }
    }

    void TestCtorWithSize() {
        cout << "    Creating ArraySequence<char> with specified length" << endl;

        bool isError = false;

        int mockLength = 3;
        Sequence<char>* charDynArr;
        try {
            charDynArr = new ArraySequence<char>(3);
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                charDynArr->Get(0);

                isError = true;
            } catch (...) {
                cout << "        SUCCESS ArraySequence<char> with " << mockLength << " was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR ArraySequence<char> with " << mockLength << " wasn't created" << endl;
        }

        cout << "    Creating ArraySequence<Object> with specified length" << endl;

        isError = false;
        Sequence<MockClass>* objectDynArr;
        try {
            objectDynArr = new ArraySequence<MockClass>(mockLength);
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                objectDynArr->Get(0);

                isError = true;
            } catch (...) {
                cout << "        SUCCESS ArraySequence<Object> with " << mockLength << " was created"  << endl;
            }
        }

        if (isError) {
            cout << "        ERROR ArraySequence<Object> with " << mockLength << " was created" << endl;
        }
    }

    void TestCtorWithDynamicArray() {
        cout << "    Creating ArraySequence<char> with source DynamicArray<char>" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char>(mockCharArray, 4);

        bool isError = false;
        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharDynArr);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharDynArr->Get(i);
            char arraySequenceValue = mockCharArraySequence->Get(i);

            if (mockValue != arraySequenceValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", arraySequence " << arraySequenceValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<char> was successful created by source DynamicArray<char>" << endl;
        }

        cout << "    Creating ArraySequence<Object> with source DynamicArray<Object>" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();
        DynamicArray<MockClass>* mockObjectDynArr = new DynamicArray<MockClass>(mockObjectArray, 3);

        Sequence<MockClass>* mockObjectArraySequence = new ArraySequence<MockClass>(mockObjectDynArr);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectDynArr->Get(i);
            MockClass arraySequenceValue = mockObjectArraySequence->Get(i);

            if (mockValue != arraySequenceValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, arraySequence: {str:  " << arraySequenceValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<Object> was successful created by source DynamicArray<Object>" << endl;
        }
    }

    void TestCopingCtor() {
        cout << "    Coping existed ArraySequence<char>" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, 4);

        bool isError = false;
        ArraySequence<char>* copiedCharDynArr = new ArraySequence<char>(*mockCharArraySequence);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char dynArrayValue = copiedCharDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", DynArr " << dynArrayValue << ")\n";
                isError = true;
            }
        }

        mockCharArraySequence->Prepend('a');

        if (mockCharArraySequence->Get(0) == copiedCharDynArr->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << mockCharArraySequence->Get(0) << "; first new: " << copiedCharDynArr->Get(0) << "). Length old: " << mockCharArraySequence->GetLength() << "; length new: " << copiedCharDynArr->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<char> was successful copied" << endl;
        }

        cout << "    Coping existed ArraySequence<Object>" << endl;
        isError = false;

        MockClass* mockObjectArray = mockObjectArrayFn();
        Sequence<MockClass>* mockObjectDynArr = new ArraySequence<MockClass>(mockObjectArray, 3);

        Sequence<MockClass>* copiedObjectDynArr = new ArraySequence<MockClass>(*mockObjectDynArr);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass dynArrayValue = copiedObjectDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, DynArr: {str:  " << dynArrayValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<Object> was successful copied" << endl;
        }
    }

    void TestGetFirst() {
        cout << "    Getting first element" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char firstValue = mockCharArraySequence->GetFirst();
        char mockFirstValue = mockCharArray[0];

        bool isError = false;
        if (firstValue != mockFirstValue) {
            cout << "        ERROR First value is not equal (source: " << mockFirstValue << ", arraySequence: " << firstValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS First value is equal" << endl;
        }
    }

    void TestGetLast() {
        cout << "    Getting last element" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char lastValue = mockCharArraySequence->GetLast();
        char mockLastValue = mockCharArray[mockArrayLength - 1];

        bool isError = false;
        if (lastValue != mockLastValue) {
            cout << "        ERROR Last value is not equal (source: " << mockLastValue << ", arraySequence: " << lastValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Last value is equal" << endl;
        }
    }

    void TestGetSubsequence() {
        cout << "    Getting subsequence" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        int startIndex = 1;
        int endIndex = 4;
        int mockLength = endIndex - startIndex;

        Sequence<char>* charSubsequence = mockCharArraySequence->GetSubsequence(startIndex, endIndex);

        bool isError = false;
        for (int i = 0; i < mockLength; i++) {
            char mockValue = mockCharArray[i + startIndex];
            char arrayValue = charSubsequence->Get(i);

            if (mockValue != arrayValue) {
                cout << "        ERROR Char elements at " << i << " are not equal (source " << mockValue << ", arraySequence " << arrayValue << ")\n";
                isError = true;
            }
        }

        mockCharArraySequence->Prepend('a');

        if (mockCharArraySequence->Get(0) == charSubsequence->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << mockCharArraySequence->Get(0) << "; first new: " << charSubsequence->Get(0) << "). Length old: " << mockCharArraySequence->GetLength() << "; length new: " << charSubsequence->GetLength() << endl;

            isError = true;
        }
        if (!isError) {
            cout << "        SUCCESS Char subsequence was successful getted" << endl;
        }
    }

    void TestGetLength() {
        cout << "    Getting ArraySequence<char> length" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        int mockLength = mockCharArraySequence->GetLength();
        if (mockArrayLength != mockLength) {
            cout << "        ERROR Length of array is not currect (source " << mockArrayLength << ", array length: " << mockLength << ")" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Array length is currect" << endl;
        }
    }

    void TestAppend() {
        cout << "    Prepending element" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char prependedChar = 'a';
        mockCharArraySequence->Prepend(prependedChar);

        bool isError = false;
        char arrayValue = mockCharArraySequence->GetFirst();

        if (prependedChar != arrayValue) {
            cout << "        ERROR Prepend function didn't work currectly (source " << prependedChar << ", array length: " << arrayValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Prepend function worked currectly" << endl;
        }
    }

    void TestPrepend() {
        cout << "    Appending element" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        mockCharArraySequence->Append(appendingChar);

        bool isError = false;
        char arrayValue = mockCharArraySequence->GetLast();

        if (appendingChar != arrayValue) {
            cout << "        ERROR Append function didn't work currectly (source " << appendingChar << ", array length: " << arrayValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Append function worked currectly" << endl;
        }
    }

    void TestInsertAt() {
        cout << "    Inserting element at" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        int insertIndex = 3;
        mockCharArraySequence->InsertAt(appendingChar, insertIndex);

        bool isError = false;
        char arrayValue = mockCharArraySequence->Get(insertIndex);
        int arrayLength = mockCharArraySequence->GetLength();

        if (appendingChar != arrayValue) {
            cout << "        ERROR InsertAt function didn't work currectly (source " << appendingChar << ", array length: " << arrayValue << ")" << endl;

            isError = true;
        }

        if (mockArrayLength + 1 != arrayLength) {
            cout << "        ERROR Inserted array length isn't currect (expected " << mockArrayLength + 1 << "; current " << arrayLength << ")" << endl;

            isError = false;
        }

        if (!isError) {
            cout << "        SUCCESS InsertAt function worked currectly" << endl;
        }
    }

    void TestRemoveAt() {
        cout << "    Removing element at" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        int removingIndex = 2;
        mockCharArraySequence->RemoveAt(removingIndex);

        bool isError = false;
        int arrayLength = mockCharArraySequence->GetLength();
        if (mockArrayLength - 1 != arrayLength) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength - 1 << "; current " << arrayLength << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS RemoveAt function worked currectly" << endl;
        }
    }

    void TestRemove() {
        cout << "    Removing element" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharArraySequence->Append(removingChar);
        mockCharArraySequence->Remove(removingChar);

        bool isError = false;
        int arrayLength = mockCharArraySequence->GetLength();
        if (mockArrayLength != arrayLength) {
            cout << "        ERROR Length shoudn't changed (expected " << mockArrayLength << "; current " << arrayLength << ")" << endl;

            isError = true;
        }

        if (removingChar != mockCharArraySequence->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharArraySequence->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Remove function worked currectly" << endl;
        }
    }

    void TestRemoveAll() {
        cout << "    Removing all elements" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharArraySequence->Append(removingChar);
        mockCharArraySequence->RemoveAll(removingChar);

        bool isError = false;
        int arrayLength = mockCharArraySequence->GetLength();
        if (mockArrayLength - 1 != arrayLength) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength - 1 << "; current " << arrayLength << ")" << endl;

            isError = true;
        }

        if (removingChar == mockCharArraySequence->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharArraySequence->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS RemoveAll function worked currectly" << endl;
        }
    }

    void TestConcat() {
        cout << "    Concating two ArraySequence<char>" << endl;

        char mockCharArrayForConcat[3] = {'e', 'l', 'b'};

        Sequence<char>* firstArray = new ArraySequence<char>(mockCharArray, mockArrayLength);
        Sequence<char>* secondArray = new ArraySequence<char>(mockCharArrayForConcat, 3);

        Sequence<char>* concatedArray = firstArray->Concat(secondArray);

        bool isError = false;
        int concatedLength = concatedArray->GetLength();
        if (concatedLength != mockArrayLength + 3) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength + 3 << "; current " << concatedLength << ")" << endl;

            isError = true;
        }

        for (int i = 0; i < 3; i++) {
            char mockValue = secondArray->Get(i);
            char arrayValue = concatedArray->Get(i + mockArrayLength);

            if (mockValue != arrayValue) {
                cout << "        ERROR Concated elements at " << i << " is not equal (source " << mockValue << ", arraySequence " << arrayValue << ")\n";
                isError = true;
            }
        }

        firstArray->Prepend('a');

        if (firstArray->Get(0) == concatedArray->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << firstArray->Get(0) << "; first new: " << concatedArray->Get(0) << "). Length old: " << firstArray->GetLength() << "; length new: " << concatedArray->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Two ArraySequence<char> were successful concatenated" << endl;
        }
    }

    void TestCopy() {
        cout << "    Coping ArraySequence<char>" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, 4);

        bool isError = false;
        Sequence<char>* copiedCharDynArr = mockCharArraySequence->Copy();
        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char arrayValue = copiedCharDynArr->Get(i);

            if (mockValue != arrayValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", arraySequence " << arrayValue << ")\n";
                isError = true;
            }
        }

        mockCharArraySequence->Prepend('a');

        if (mockCharArraySequence->Get(0) == copiedCharDynArr->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << mockCharArraySequence->Get(0) << "; first new: " << copiedCharDynArr->Get(0) << "). Length old: " << mockCharArraySequence->GetLength() << "; length new: " << copiedCharDynArr->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<char> was successful copied" << endl;
        }
    }

    void TestCopyTo() {
        cout << "    Coping ArraySequence<char> to ArraySequence<char>" << endl;

        Sequence<char>* mockCharArraySequence = new ArraySequence<char>(mockCharArray, 4);

        char targetCharArray[3] = {'e', 'l', 'b'};
        Sequence<char>* targetArraySequence = new ArraySequence<char>(targetCharArray, 3);

        mockCharArraySequence->CopyTo(targetArraySequence, 1);

        bool isError = false;
        if (targetCharArray[0] != targetArraySequence->GetFirst()) {
            cout << "        ERROR Char elements at 0 are not equal (source " << targetCharArray[0] << ", arraySequence " << targetArraySequence->GetFirst() << ")" << endl;

            isError = true;
        }

        for (int i = 1 ; i < 5; i++) {
            char mockValue = mockCharArray[i - 1];
            char arraySequenceValue = targetArraySequence->Get(i);

            if (mockValue != arraySequenceValue) {
                cout << "        ERROR Char elements at 0 are not equal (source " << targetCharArray[0] << ", arraySequence " << targetArraySequence->GetFirst() << ")" << endl;

                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS ArraySequence<char> was successful copied" << endl;
        }
    }
};

