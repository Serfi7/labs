#pragma once

#include "iostream"

#include "../include/dictionary/Dictionary.hpp"
#include "../include/dictionary/IDictionary.hpp"
#include "./Mock.hpp"

using namespace std;
using namespace Mock;

class DictionaryTest {
public:
    DictionaryTest() {
        TestConstructor();
        cout << endl;
        TestAdd();
        cout << endl;
        TestDestructor();
        cout << endl;
        TestGetCount();
        cout << endl;
        TestGet();
        cout << endl;
        TestContainsKey();
        cout << endl;
        TestRemove();
        cout << endl;
    }

private:
    IDictionary<string, Cat>* InitTree() {
        return nullptr;
    }

    void TestConstructor() {
        cout << "    Creating Dictionary<int, Cat>" << endl;

        new Dictionary<int, Cat>();

        cout << "        SUCCESS Dictionary<string, Cat> was created" << endl;
    }

    void TestAdd() {
        cout << "    Adding Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);

        catMap->Add("123", cat1);

        bool isError = false;

        try {
            catMap->Add("123", cat2);

            isError = true;

            cout << "        ERROR Added key, which existed in dictionary" << endl;
        } catch (...) {}

        catMap->Add("111", cat3);

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> addition works good" << endl;
        }
    }

    void TestDestructor() {
        cout << "    Deleting Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);

        catMap->Add("121", cat3);
        catMap->Add("122", cat1);
        catMap->Add("123", cat2);

        bool isError = false;

        try {
            delete catMap;
        } catch (...) {
            isError = true;

            cout << "        ERROR Could not delete Dictionary<string, Cat>" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> was deleted" << endl;
        }
    }

    void TestGetCount() {
        cout << "    Getting count Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);
        Cat cat4 = Cat("Nikita", 8);
        Cat cat5 = Cat("Serega", 5);

        catMap->Add("122", cat1);
        catMap->Add("121", cat3);
        catMap->Add("123", cat2);
        catMap->Add("1111", cat4);
        catMap->Add("222", cat5);

        bool isError = false;

        if (catMap->GetCount() != 5)  {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat>.GetCount is wrong" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> has correct count" << endl;
        }
    }

    void TestGet() {
        cout << "    Getting cats Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);
        Cat cat4 = Cat("Nikita", 8);
        Cat cat5 = Cat("Serega", 5);

        Cat catsArray[] = {cat1, cat2, cat3, cat4, cat5};
        string keysArray[] = { "122", "121", "123", "1111", "222" };

        for (int i = 0; i < 5; i++) {
            catMap->Add(keysArray[i], catsArray[i]);
        }

        bool isError = false;

        for (int i = 0; i < 5; i++) {
            if (catMap->Get(keysArray[i]) == catsArray[i]) {
                continue;
            }

            isError = true;

            cout << "        ERROR Dictionary<string, Cat> return wrong Cat" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> returned currect cats" << endl;
        }
    }

    void TestContainsKey() {
        cout << "    Getting cats Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);
        Cat cat4 = Cat("Nikita", 8);
        Cat cat5 = Cat("Serega", 5);

        Cat catsArray[] = {cat1, cat2, cat3, cat4, cat5};
        string keysArray[] = { "122", "121", "123", "1111", "222" };

        for (int i = 0; i < 5; i++) {
            catMap->Add(keysArray[i], catsArray[i]);
        }

        bool existentKey = catMap->ContainsKey("123") && catMap->ContainsKey("1111");
        bool nonexistentKey = catMap->ContainsKey("0000") || catMap->ContainsKey("11111");

        bool isError = false;

        if (!existentKey) {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat> existent key is non contains" << endl;
        }

        if (nonexistentKey) {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat> nonexistent key is contains" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> contains keys works good" << endl;
        }
    }

    void TestRemove() {
        cout << "    Removing cats Dictionary<string, Cat>" << endl;

        auto catMap = new Dictionary<string, Cat>();

        Cat cat1 = Cat("Barcik", 2);
        Cat cat2 = Cat("Vacya", 1);
        Cat cat3 = Cat("Misha", 4);
        Cat cat4 = Cat("Nikita", 8);
        Cat cat5 = Cat("Serega", 5);

        Cat catsArray[] = {cat1, cat2, cat3, cat4, cat5};
        string keysArray[] = { "122", "121", "123", "1111", "222" };

        for (int i = 0; i < 5; i++) {
            catMap->Add(keysArray[i], catsArray[i]);
        }

        bool isError = false;

        catMap->Remove(keysArray[4]);
        bool isDeletedContains = catMap->ContainsKey(keysArray[4]);

        if (isDeletedContains) {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat> doesn't delete element" << endl;
        }

        catMap->Add(keysArray[4], catsArray[4]);

        catMap->Remove(keysArray[3]);
        isDeletedContains = catMap->ContainsKey(keysArray[3]);
        bool containsLeaf = catMap->ContainsKey(keysArray[4]);
        bool leafWrong = !containsLeaf || catsArray[4] != catMap->Get(keysArray[4]);

        if (isDeletedContains || leafWrong) {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat> doesn't delete element" << endl;
        }

        catMap->Remove(keysArray[0]);
        isDeletedContains = catMap->ContainsKey(keysArray[0]);
        containsLeaf = catMap->ContainsKey(keysArray[1]);
        leafWrong = !containsLeaf || catsArray[1] != catMap->Get(keysArray[1]);

        if (isDeletedContains || leafWrong) {
            isError = true;

            cout << "        ERROR Dictionary<string, Cat> doesn't delete element" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Dictionary<string, Cat> deletes elements good" << endl;
        }
    }
};
