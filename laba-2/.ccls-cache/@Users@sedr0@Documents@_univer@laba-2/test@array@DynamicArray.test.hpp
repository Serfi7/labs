#pragma once

#include "iostream"

#include "../../include/array/DynamicArray.hpp"
#include "../Mock.hpp"

using namespace std;
using namespace Mock;

class DynamicArrayTest {
public:
    DynamicArrayTest() {
        TestCtorWithArray();
        cout << endl;
        TestCtorWithSize();
        cout << endl;
        TestCopingCtor();
        cout << endl;

        TestSize();
        cout << endl;
        TestSet();
        cout << endl;
        TestResize();
    }

private:
    void TestCtorWithArray() {
        cout << "    Creating DynamicArray<char> by source char array" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        for (int i = 0; i < mockArrayLength; i++) {
            char mockValue = mockCharArray[i];
            char dynArrayValue = mockCharDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Char elements at " << i << " is not equal (source " << mockValue << ", DynArray " << dynArrayValue << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS DynamicArray<char> was successful created by mock array" << endl;
        }

        cout << "    Creating DynamicArray<char> by source char array with zero and less length" << endl;

        try {
            mockCharDynArr = new DynamicArray<char>(mockCharArray, 0);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS DynamicArray<char> with zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR DynamicArray<char> with zero length was created" << endl;
        }

        try {
            mockCharDynArr = new DynamicArray<char>(mockCharArray, -1);

            isError = true;
        } catch (...) {
            cout << "        SUCCESS DynamicArray<char> with less zero length wasn't created" << endl;

            isError = false;
        }

        if (isError) {
            cout << "        ERROR DynamicArray<char> with less zero length was created" << endl;
        }

        cout << "    Creating DynamicArray<Object> by source char array" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();

        DynamicArray<MockClass>* mockObjectDynArr = new DynamicArray<MockClass>(mockObjectArray, 3);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass dynArrayValue = mockObjectDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, DynArray: {str:  " << dynArrayValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS DynamicArray<Object> was successful created by mock array" << endl;
        }
    }

    void TestCtorWithSize() {
        cout << "    Creating DynamicArray<char> with specified length" << endl;

        bool isError = false;

        int mockLength = 3;
        DynamicArray<char>* charDynArr;
        try {
            charDynArr = new DynamicArray<char>(3);
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                charDynArr->Get(0);

                isError = true;
            } catch (...) {
                cout << "        SUCCESS DynamicArray<char> with " << mockLength << " was created" << endl;
            }
        }

        if (isError) {
            cout << "        ERROR DynamicArray<char> with " << mockLength << " wasn't created" << endl;
        }

        cout << "    Creating DynamicArray<Object> with specified length" << endl;

        isError = false;
        DynamicArray<MockClass>* objectDynArr;
        try {
            objectDynArr = new DynamicArray<MockClass>(mockLength);
        } catch (...) {
            isError = true;
        }

        if (!isError) {
            try {
                objectDynArr->Get(0);

                isError = true;
            } catch (...) {
                cout << "        SUCCESS DynamicArray<Object> with " << mockLength << " was created"  << endl;
            }
        }

        if (isError) {
            cout << "        ERROR DynamicArray<Object> with " << mockLength << " was created" << endl;
        }
    }

    void TestCopingCtor() {
        cout << "    Coping existed DynamicArray<char>" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char>(mockCharArray, 4);

        bool isError = false;
        DynamicArray<char>* copiedCharDynArr = new DynamicArray<char>(*mockCharDynArr);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char dynArrayValue = copiedCharDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", DynArr " << dynArrayValue << ")\n";
                isError = true;
            }
        }

        DynamicArray<char>* arrayFromCopiedArr = new DynamicArray<char>(*mockCharDynArr);

        copiedCharDynArr->Resize(5);

        for (int i = 0; i < 4; i++) {
            char mockValue = mockCharArray[i];
            char dynArrayValue = arrayFromCopiedArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Element at " << i << " is not equal (source " << mockValue << ", DynArr " << dynArrayValue << ")\n";
                isError = true;
            }
        }
        if (!isError) {
            cout << "        SUCCESS DynamicArray<char> was successful copied" << endl;
        }

        cout << "    Coping existed DynamicArray<Object>" << endl;

        MockClass* mockObjectArray = mockObjectArrayFn();
        DynamicArray<MockClass>* mockObjectDynArr = new DynamicArray<MockClass>(mockObjectArray, 3);

        DynamicArray<MockClass>* copiedObjectDynArr = new DynamicArray<MockClass>(*mockObjectDynArr);

        for (int i = 0; i < 3; i++) {
            MockClass mockValue = mockObjectArray[i];
            MockClass dynArrayValue = copiedObjectDynArr->Get(i);

            if (mockValue != dynArrayValue) {
                cout << "        ERROR Object elements at " << i << " is not equal (source: {str: " << mockValue.str << ", num: " << mockValue.num << "}, DynArr: {str:  " << dynArrayValue.str << ", num: " << mockValue.num << "}" << ")\n";
                isError = true;
            }
        }

        if (!isError) {
            cout << "        SUCCESS DynamicArray<Object> was successful copied" << endl;
        }
    }

    void TestSize(){
        cout << "    Getting DynamicArray<char> size" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char>(mockCharArray, mockArrayLength);

        bool isError = false;
        if (mockArrayLength != mockCharDynArr->Size()) {
            cout << "        ERROR Char DynamicArray<char> is not currect (expected length: " << mockArrayLength << "; DynArr length: " << mockCharDynArr->Size() << ")" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Length is currect" << endl;
        }
    }

    void TestSet(){
        cout << "    Setting DynamicArray<char> element" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char> (3);

        mockCharDynArr->Set(2, 's');

        bool isError = false;
        if ('s' != mockCharDynArr->Get(2)) {
            cout << "        ERROR Set method worked uncorrectly (expected: s; DynArr: "<< mockCharDynArr->Get(2) << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Set method worked corretly" << endl;
        }
    }

    void TestResize() {
        cout << "    Resizing DynamicArray<char>" << endl;

        DynamicArray<char>* mockCharDynArr = new DynamicArray<char> (mockCharArray, mockArrayLength);

        mockCharDynArr->Resize(mockArrayLength - 1);

        bool isError = false;
        char mockValue = mockCharArray[mockArrayLength - 2];
        char dynArrValue = mockCharDynArr->Get(mockArrayLength - 2);
        if (mockValue != dynArrValue) {
            cout << "        ERROR Last element isn't expected (expected: " << mockValue << "; DynArr: " << dynArrValue << ")" << endl;

            isError = true;
        }

        if (mockArrayLength - 1 != mockCharDynArr->Size()) {
            cout << "        ERROR DynamicArray<char> length isn't currect (expected: " << mockArrayLength - 1 << "; DynArr length: " << mockCharDynArr->Size() << ")" << endl;

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Resize worked currently" << endl;
        }
    }
};
