#pragma once

#include "../../include/list/LinkedListSequence.hpp"
#include "../../include/array/ArraySequence.hpp"
#include "../Mock.hpp"

using namespace std;
using namespace Mock;

class LinkedListSequenceTest {
public:
    LinkedListSequenceTest() {
        TestCtorWithArray();
        cout << endl;
        TestEmptyCtor();
        cout << endl;
        TestCtorWithLinkedList();
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
        TestInsertAt();
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
        cout << "    Creating LinkedListSequence<char> by source char array" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        for (int i = 0; i < mockArrayLength; i++) {
            char mockValue = mockCharArray[i];
            char listSequenceValue = mockCharListSequence->Get(i);

            if (mockValue != listSequenceValue) {
                cout << "        ERROR Char elements at " << i << " are not equal (source " << mockValue << ", listSequence " << listSequenceValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<char> was successful created by mock array" << endl;
        }

        cout << "    Creating LinkedListSequence<char> by source char array with zero and less length" << endl;

        try {
            mockCharListSequence = new LinkedListSequence<char>(mockCharArray, 0);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS LinkedListSequence<char> with zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR LinkedListSequence<char> with zero length was created" << endl;
        }

        try {
            mockCharListSequence = new LinkedListSequence<char>(mockCharArray, -1);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS LinkedListSequence<char> with less zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR LinkedListSequence<char> with less zero length was created" << endl;
        }

        cout << "    Creating LinkedListSequence<Object> by source char array" << endl;

        Mock::MockClass* mockObjectArray = Mock::mockObjectArrayFn();

        Sequence<MockClass>* mockObjectListSequence = new LinkedListSequence<MockClass>(mockObjectArray, 3);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass listSequenceValue = mockObjectListSequence->Get(i);

            if (mockValue != listSequenceValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, ListSequence: {str:  " << listSequenceValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<Object> was successful created by mock array" << endl;
        }
    }

    void TestEmptyCtor() {
        cout << "    Creating empty LinkedListSequence<char>" << endl;

        bool isError = false;

        Sequence<char>* charListSequence;
        try {
            charListSequence = new LinkedListSequence<char>();
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                charListSequence->GetFirst();

                isError = true;
            } catch (...) {
                cout << "        SUCCESS Empty LinkedListSequence<char> was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR Empty LinkedListSequence<char> wasn't created" << endl;
        }

        cout << "    Creating empty LinkedListSequence<Object>" << endl;

        isError = false;
        Sequence<MockClass>* objectListSequence;
        try {
            objectListSequence = new LinkedListSequence<MockClass>();
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                objectListSequence->GetFirst();

                isError = true;
            } catch (...) {
                cout << "        SUCCESS Empty LinkedListSequence<Object> was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR Empty LinkedListSequence<Object> wasn't created" << endl;
        }
    }

    void TestCtorWithLinkedList() {
        cout << "    Creating LinkedListSequence<char> with source LinkedList<char>" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, 4);

        bool isError = false;
        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharList);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharList->Get(i);
            char listSequenceValue = mockCharListSequence->Get(i);

            if (mockValue != listSequenceValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", ListSequence " << listSequenceValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<char> was successful created by source LinkedList<char>" << endl;
        }

        cout << "    Creating LinkedListSequence<Object> with source LinkedList<Object>" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();
        LinkedList<MockClass>* mockObjectList = new LinkedList<MockClass>(mockObjectArray, 3);

        Sequence<MockClass>* mockObjectListSequence = new LinkedListSequence<MockClass>(mockObjectList);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectList->Get(i);
            MockClass listSequenceValue = mockObjectListSequence->Get(i);

            if (mockValue != listSequenceValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, ListSequence: {str:  " << listSequenceValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<Object> was successful created by source LinkedList<Object>" << endl;
        }
    }

    void TestCopingCtor() {
        cout << "    Coping existed LinkedListSequence<char>" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, 4);

        bool isError = false;
        Sequence<char>* copiedCharList = new LinkedListSequence<char>(*mockCharListSequence);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char listValue = copiedCharList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", ListSequence " << listValue << ")\n";
                isError = true;
            }
        }

        mockCharListSequence->Prepend('a');

        if (mockCharListSequence->Get(0) == copiedCharList->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << mockCharListSequence->Get(0) << "; first new: " << copiedCharList->Get(0) << "). Length old: " << mockCharListSequence->GetLength() << "; length new: " << copiedCharList->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<char> was successful copied" << endl;
        }

        cout << "    Coping existed LinkedListSequence<Object>" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();
        Sequence<MockClass>* mockObjectListSequence = new LinkedListSequence<MockClass>(mockObjectArray, 3);

        Sequence<MockClass>* copiedObjectListSequence = new LinkedListSequence<MockClass>(*mockObjectListSequence);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass listValue = copiedObjectListSequence->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, ListSequence: {str:  " << listValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<Object> was successful copied" << endl;
        }
    }

    void TestGetFirst() {
        cout << "    Getting first element" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char firstValue = mockCharListSequence->GetFirst();
        char mockFirstValue = mockCharArray[0];

        bool isError = false;
        if (firstValue != mockFirstValue) {
            cout << "        ERROR First value is not equal (source: " << mockFirstValue << ", ListSequence: " << firstValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS First value is equal" << endl;
        }
    }

    void TestGetLast() {
        cout << "    Getting last element" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char lastValue = mockCharListSequence->GetLast();
        char mockLastValue = mockCharArray[mockArrayLength - 1];

        bool isError = false;
        if (lastValue != mockLastValue) {
            cout << "        ERROR Last value is not equal (source: " << mockLastValue << ", ListSequence: " << lastValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Last value is equal" << endl;
        }
    }

    void TestGetSubsequence() {
        cout << "    Getting subsequence" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        int startIndex = 1;
        int endIndex = 4;
        int mockLength = endIndex - startIndex;

        Sequence<char>* charSubsequence = mockCharListSequence->GetSubsequence(startIndex, endIndex);

        bool isError = false;
        for (int i = 0; i < mockLength; i++) {
            char mockValue = mockCharArray[i + startIndex];
            char listValue = charSubsequence->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Char elements at " << i << " are not equal (source " << mockValue << ", ListSequence " << listValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS Char subsequence was successful getted" << endl;
        }
    }

    void TestGetLength() {
        cout << "    Getting LinkedListSequence<char> length" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        int mockLength = mockCharListSequence->GetLength();
        if (mockArrayLength != mockLength) {
            cout << "        ERROR Length of list is not currect (source " << mockArrayLength << ", list length: " << mockLength << ")" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS List length is currect" << endl;
        }
    }

    void TestPrepend() {
        cout << "    Prepending element" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char prependedChar = 'a';
        mockCharListSequence->Prepend(prependedChar);

        bool isError = false;
        char listValue = mockCharListSequence->GetFirst();

        if (prependedChar != listValue) {
            cout << "        ERROR Prepend function didn't work currectly (source " << prependedChar << ", list length: " << listValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Prepend function worked currectly" << endl;
        }
    }

    void TestAppend() {
        cout << "    Appending element" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        mockCharListSequence->Append(appendingChar);

        bool isError = false;
        char listValue = mockCharListSequence->GetLast();

        if (appendingChar != listValue) {
            cout << "        ERROR Append function didn't work currectly (source " << appendingChar << ", list length: " << listValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Append function worked currectly" << endl;
        }
    }

    void TestInsertAt() {
        cout << "    Inserting element at" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        int insertIndex = 3;
        mockCharListSequence->InsertAt(appendingChar, insertIndex);

        bool isError = false;
        char listValue = mockCharListSequence->Get(insertIndex);
        int listLength = mockCharListSequence->GetLength();

        if (appendingChar != listValue) {
            cout << "        ERROR InsertAt function didn't work currectly (source " << appendingChar << ", list length: " << listValue << ")" << endl;

            isError = true;
        }

        if (mockArrayLength + 1 != listLength) {
            cout << "        ERROR Inserted list length isn't currect (expected " << mockArrayLength + 1 << "; current " << listLength << ")" << endl;

            isError = false;
        }

        if (!isError) {
            cout << "        SUCCESS InsertAt function worked currectly" << endl;
        }
    }

    void TestRemoveAt() {
        cout << "    Removing element at" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        int removingIndex = 2;
        mockCharListSequence->RemoveAt(removingIndex);

        bool isError = false;
        int listLength = mockCharListSequence->GetLength();
        if (mockArrayLength - 1 != listLength) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength - 1 << "; current " << listLength << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS RemoveAt function worked currectly" << endl;
        }
    }

    void TestRemove() {
        cout << "    Removing element" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharListSequence->Append(removingChar);
        mockCharListSequence->Remove(removingChar);

        bool isError = false;
        int listLength = mockCharListSequence->GetLength();
        if (mockArrayLength != listLength) {
            cout << "        ERROR Length shoudn't changed (expected " << mockArrayLength << "; current " << listLength << ")" << endl;

            isError = true;
        }

        if (removingChar != mockCharListSequence->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharListSequence->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Remove function worked currectly" << endl;
        }
    }

    void TestRemoveAll() {
        cout << "    Removing all elements" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharListSequence->Append(removingChar);
        mockCharListSequence->RemoveAll(removingChar);

        bool isError = false;
        int listLength = mockCharListSequence->GetLength();
        if (mockArrayLength - 1 != listLength) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength - 1 << "; current " << listLength << ")" << endl;

            isError = true;
        }

        if (removingChar == mockCharListSequence->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharListSequence->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS RemoveAll function worked currectly" << endl;
        }
    }

    void TestConcat() {
        cout << "    Concating two LinkedListSequence<char>" << endl;

        char mockCharArrayForConcat[3] = {'e', 'l', 'b'};

        Sequence<char>* firstList = new LinkedListSequence<char>(mockCharArray, mockArrayLength);
        Sequence<char>* secondList = new LinkedListSequence<char>(mockCharArrayForConcat, 3);

        Sequence<char>* concatedList = firstList->Concat(secondList);

        bool isError = false;
        int concatedLength = concatedList->GetLength();
        if (concatedLength != mockArrayLength + 3) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength + 3 << "; current " << concatedLength << ")" << endl;

            isError = true;
        }

        for (int i = 0; i < 3; i++) {
            char mockValue = secondList->Get(i);
            char listValue = concatedList->Get(i + mockArrayLength);

            if (mockValue != listValue) {
                cout << "        ERROR Concated elements at " << i << " is not equal (source " << mockValue << ", list " << listValue << ")\n";
                isError = true;
            }
        }

        firstList->Prepend('a');

        if (firstList->Get(0) == concatedList->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << firstList->Get(0) << "; first new: " << concatedList->Get(0) << "). Length old: " << firstList->GetLength() << "; length new: " << concatedList->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Two LinkedListSequence<char> were successful concatenated" << endl;
        }

    }

    void TestCopy() {
        cout << "    Coping LinkedListSequence<char>" << endl;

        Sequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, 4);

        bool isError = false;
        Sequence<char>* copiedCharList = mockCharListSequence->Copy();
        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char listValue = copiedCharList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", ListSequence " << listValue << ")\n";
                isError = true;
            }
        }

        mockCharListSequence->Prepend('a');

        if (mockCharListSequence->Get(0) == copiedCharList->Get(0)) {
            cout << "        ERROR Changing in old array changed new array (first old: " << mockCharListSequence->Get(0) << "; first new: " << copiedCharList->Get(0) << "). Length old: " << mockCharListSequence->GetLength() << "; length new: " << copiedCharList->GetLength() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS LinkedListSequence<char> was successful copied" << endl;
        }
    }

    void TestCopyTo() {
        cout << "    Coping LinkedListSequence<char> to LinkedListSequence<char>" << endl;

        LinkedListSequence<char>* mockCharListSequence = new LinkedListSequence<char>(mockCharArray, 4);

        char targetCharArray[3] = {'e', 'l', 'b'};
        LinkedListSequence<char>* targetListSequence = new LinkedListSequence<char>(targetCharArray, 3);

        mockCharListSequence->CopyTo(targetListSequence, 1);

        bool isError = false;
        if (targetCharArray[0] != targetListSequence->GetFirst()) {
            cout << "        ERROR Char elements at 0 are not equal (source " << targetCharArray[0] << ", listSequence " << targetListSequence->GetFirst() << ")" << endl;

            isError = true;
        }

        for (int i = 1 ; i < 5; i++) {
            char mockValue = mockCharArray[i - 1];
            char listSequenceValue = targetListSequence->Get(i);

            if (mockValue != listSequenceValue) {
                cout << "        ERROR Char elements at 0 are not equal (source " << targetCharArray[0] << ", listSequence " << targetListSequence->GetFirst() << ")" << endl;

                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedList<char> was successful copied" << endl;
        }
    }
};

