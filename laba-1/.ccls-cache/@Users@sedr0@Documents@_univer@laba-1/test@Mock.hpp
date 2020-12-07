#pragma once

#include "iostream"

namespace Mock {
    const int mockArrayLength = 5;
    char mockCharArray[mockArrayLength] = {'n', 'm', 'i', 'j', 'k'};
    char mockSortedCharArray[mockArrayLength] = {'i', 'j', 'k','m', 'n'};

    int mockIntArray[5] = {457, 34, 5115, 85201, 4};
    int mockSortedIntArray[5] = {4, 34, 457, 5115, 85201};

    class MockClass {
    public:
        std::string str;
        int num;

        MockClass() {
            this->str = "";
            this->num = 0;
        }

        MockClass(std::string str, int num) {
            this->str = str;
            this->num = num;
        }

        bool operator==(const MockClass &other) {
            return this->str == other.str && this->num == other.num;
        }

        bool operator!=(const MockClass &other) {
            return !(*this == other);
        }
    };

    MockClass* mockObjectArrayFn() {
        MockClass* mockObj1 = new MockClass("abc", 123);
        MockClass* mockObj2 = new MockClass("def", 456);
        MockClass* mockObj3 = new MockClass("ghi", 789);

        MockClass* mockClassArray = static_cast<MockClass*>(operator new[](3 * sizeof(MockClass)));
        mockClassArray[0] = *mockObj1;
        mockClassArray[1] = *mockObj2;
        mockClassArray[2] = *mockObj3;

        return mockClassArray;
    };

    int listMatrixSize = 3;
    int matrixLine[3] = { 1, 2, 3 };
}
