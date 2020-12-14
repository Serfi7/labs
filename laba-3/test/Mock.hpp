#pragma once

#include "iostream"

#include "../include/array/ArraySequence.hpp"

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

    class Cat {
    public:
        std::string name;
        int age;

        Cat() : name(""), age(1111) {}
        Cat(std::string name, int age) 
            : name(name),
            age(age)
        {}

        bool operator==(const Cat &other) {
            return this->name == other.name && this->age == other.age;
        }

        bool operator!=(const Cat &other) {
            return !(*this == other);
        }

        bool operator<(const Cat &other) const {
            return age < other.age;
        }

        bool operator>(const Cat &other) const {
            return age > other.age;
        }

        friend std::ostream& operator<<(std::ostream &os, Cat &cat) {
            os <<
                "Name: " <<
                cat.name <<
                ", age: " <<
                cat.age;

            return os;
        }
    };

    Sequence<Cat>* getCatsArray() {
        Cat cat1 = Cat("Barcik", 2); // 0
        Cat cat2 = Cat("Vacya", 1);  // 1
        Cat cat3 = Cat("Micha", 8);  // 2
        Cat cat4 = Cat("Kolya", 14); // 3
        Cat cat5 = Cat("Nikita", 4); // 4
        Cat cat6 = Cat("Serge", 88); // 5
        Cat cat7 = Cat("Leo", 33);   // 6
        Cat cat8 = Cat("Ivan", 5);   // 7

        Sequence<Cat>* catsArr = new ArraySequence<Cat>(8);
        catsArr->Append(cat1);
        catsArr->Append(cat2);
        catsArr->Append(cat3);
        catsArr->Append(cat4);
        catsArr->Append(cat5);
        catsArr->Append(cat6);
        catsArr->Append(cat7);
        catsArr->Append(cat8);

        return catsArr;
    }
}
