#pragma once

#include "../../include/list/LinkedList.hpp"
#include "../../include/Exception.hpp"
#include "../Mock.hpp"

using namespace std;
using namespace Mock;

class LinkedListTest {
public:
    LinkedListTest() {
        TestCtorWithArray();
        cout << endl;
        TestEmptyCtor();
        cout << endl;
        TestCopingCtor();
        cout << endl;

        TestGetFirst();
        cout << endl;
        TestGetLast();
        cout << endl;
        TestGetSublist();
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
    }

private:
    void TestCtorWithArray() {
        cout << "    Creating LinkedList<char> by source char array" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        for (int i = 0; i < mockArrayLength; i++) {
            char mockValue = mockCharArray[i];
            char listValue = mockCharList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Char elements at " << i << " is not equal (source " << mockValue << ", list " << listValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedList<char> was successful created by mock array" << endl;
        }

        cout << "    Creating LinkedList<char> by source char array with zero and less length" << endl;

        try {
            mockCharList = new LinkedList<char>(mockCharArray, 0);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS LinkedList<char> with zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR LinkedList<char> with zero length was created" << endl;
        }

        try {
            mockCharList = new LinkedList<char>(mockCharArray, -1);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS LinkedList<char> with less zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR LinkedList<char> with less zero length was created" << endl;
        }

        cout << "    Creating LinkedList<Object> by source char array" << endl;

        Mock::MockClass* mockObjectArray = Mock::mockObjectArrayFn();

        LinkedList<MockClass>* mockObjectList = new LinkedList<MockClass>(mockObjectArray, 3);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass listValue = mockObjectList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, list: {str:  " << listValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedList<Object> was successful created by mock array" << endl;
        }
    }

    void TestEmptyCtor() {
        cout << "    Creating empty LinkedList<char>" << endl;

        bool isError = false;

        LinkedList<char>* charList;
        try {
            charList = new LinkedList<char>();
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                charList->GetFirst();

                isError = true;
            } catch (...) {
                cout << "        SUCCESS Empty LinkedList<char> was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR Empty LinkedList<char> wasn't created" << endl;
        }

        cout << "    Creating empty LinkedList<Object>" << endl;

        isError = false;
        LinkedList<MockClass>* objectList;
        try {
            objectList = new LinkedList<MockClass>();
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                objectList->GetFirst();

                isError = true;
            } catch (...) {
                cout << "        SUCCESS Empty LinkedList<Object> was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR Empty LinkedList<Object> wasn't created" << endl;
        }
    }

    void TestCopingCtor() {
        cout << "    Coping existed LinkedList<char>" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, 4);

        bool isError = false;
        LinkedList<char>* copiedCharList = new LinkedList<char>(*mockCharList);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char listValue = copiedCharList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", list " << listValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedList<char> was successful copied" << endl;
        }

        cout << "    Coping existed LinkedList<Object>" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();
        LinkedList<MockClass>* mockObjectList = new LinkedList<MockClass>(mockObjectArray, 3);

        LinkedList<MockClass>* copiedObjectList = new LinkedList<MockClass>(*mockObjectList);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass listValue = copiedObjectList->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, list: {str:  " << listValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS LinkedList<Object> was successful copied" << endl;
        }
    }
private:
    void TestGetFirst() {
        cout << "    Getting first element" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char firstValue = mockCharList->GetFirst();
        char mockFirstValue = mockCharArray[0];

        bool isError = false;
        if (firstValue != mockFirstValue) {
            cout << "        ERROR First value is not equal (source: " << mockFirstValue << ", list: " << firstValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS First value is equal" << endl;
        }
    }

    void TestGetLast() {
        cout << "    Getting last element" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char lastValue = mockCharList->GetLast();
        char mockLastValue = mockCharArray[mockArrayLength - 1];

        bool isError = false;
        if (lastValue != mockLastValue) {
            cout << "        ERROR Last value is not equal (source: " << mockLastValue << ", list: " << lastValue << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Last value is equal" << endl;
        }
    }

    void TestGetSublist() {
        cout << "    Getting sublist" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        int startIndex = 1;
        int endIndex = 4;
        int mockLength = endIndex - startIndex;

        LinkedList<char>* charSublist = mockCharList->GetSubList(startIndex, endIndex);

        bool isError = false;
        for (int i = 0; i < mockLength; i++) {
            char mockValue = mockCharArray[i + startIndex];
            char listValue = charSublist->Get(i);

            if (mockValue != listValue) {
                cout << "        ERROR Char elements at " << i << " are not equal (source " << mockValue << ", list " << listValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS Char sublist was successful getted" << endl;
        }
    }

    void TestGetLength() {
        cout << "    Getting LinkedList<char> length" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        int mockLength = mockCharList->GetLength();
        if (mockArrayLength != mockLength) {
            cout << "        ERROR Length of list is not currect (source " << mockArrayLength << ", list length: " << mockLength << ")" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS List length is currect" << endl;
        }
    }

    void TestPrepend() {
        cout << "    Prepending element" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char prependedChar = 'a';
        mockCharList->Prepend(prependedChar);

        bool isError = false;
        char listValue = mockCharList->GetFirst();

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

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        mockCharList->Append(appendingChar);

        bool isError = false;
        char listValue = mockCharList->GetLast();

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

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char appendingChar = 'a';
        int insertIndex = 3;
        mockCharList->InsertAt(appendingChar, insertIndex);

        bool isError = false;
        char listValue = mockCharList->Get(insertIndex);
        int listLength = mockCharList->GetLength();

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

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        int removingIndex = 2;
        mockCharList->RemoveAt(removingIndex);

        bool isError = false;
        int listLength = mockCharList->GetLength();
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

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharList->Append(removingChar);
        mockCharList->Remove(removingChar);

        bool isError = false;
        int listLength = mockCharList->GetLength();
        if (mockArrayLength != listLength) {
            cout << "        ERROR Length shoudn't changed (expected " << mockArrayLength << "; current " << listLength << ")" << endl;

            isError = true;
        }

        if (removingChar != mockCharList->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharList->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Remove function worked currectly" << endl;
        }
    }

    void TestRemoveAll() {
        cout << "    Removing all elements" << endl;

        LinkedList<char>* mockCharList = new LinkedList<char>(mockCharArray, mockArrayLength);

        char removingChar = 'm';
        mockCharList->Append(removingChar);
        mockCharList->RemoveAll(removingChar);

        bool isError = false;
        int listLength = mockCharList->GetLength();
        if (mockArrayLength - 1 != listLength) {
            cout << "        ERROR Length is not reduced (expected " << mockArrayLength - 1 << "; current " << listLength << ")" << endl;

            isError = true;
        }

        if (removingChar == mockCharList->GetLast()) {
            cout << "        ERROR Last element isn't expected (expected " << removingChar << "; current " << mockCharList->GetLast() << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS RemoveAll function worked currectly" << endl;
        }
    }

    void TestConcat() {
        cout << "    Concating two LinkedList<char>" << endl;

        char mockCharArrayForConcat[3] = {'e', 'l', 'b'};

        LinkedList<char>* firstList = new LinkedList<char>(mockCharArray, mockArrayLength);
        LinkedList<char>* secondList = new LinkedList<char>(mockCharArrayForConcat, 3);

        LinkedList<char>* concatedList = firstList->Concat(secondList);

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

        if (!isError) {
            cout << "        SUCCESS Two LinkedList<char> were successful concatenated" << endl;
        }
    }
};
