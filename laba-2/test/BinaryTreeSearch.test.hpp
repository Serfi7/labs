#pragma once

#include "iostream"

#include "../include/binary-search-tree/BinarySearchTree.hpp"
#include "../include/binary-search-tree/BinaryTreeBuilder.hpp"
#include "./Mock.hpp"

using namespace std;
using namespace Mock;

class BinarySearchTreeTest {
public:
    BinarySearchTreeTest() {
        TestDestructor();
        cout << endl;
        TestGetCount();
        cout << endl;
        TestGet();
        cout << endl;
        TestContains();
        cout << endl;
        TestAdd();
        cout << endl;
        TestRemove();
    }

private:
    void TestDestructor() {
        cout << "    Deleting BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        bool isError = false;

        try {
            delete catTree;
        } catch (Exception ex) {
            isError = true;
            cout << "        ERROR Couldn't delete BinarySearchTree<Cat>" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS BinarySearchTree<Cat> deleted" << endl;
        }
    }

    void TestGetCount() {
        cout << "    Getting count of BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        bool isError = false;

        if (catTree->GetCount() != catsArray->GetLength()) {
            isError = true;

            cout << "        ERROR Lenght of tree and array is not equal (tree : " << catTree->GetCount() << "; array: " << catsArray->GetLength() << ")" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Length of tree and array is equal" << endl;
        }
    }

    void TestGet() {
        cout << "    Getting Cat from BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        auto cat = catsArray->Get(0);
        auto catFromTree = catTree->Get(cat);

        bool isError = false;

        if (cat.name != catFromTree.name || cat.age != catFromTree.age) {
            isError = true;

            cout << "        ERROR Get wrong item" << endl;
        }
        
        if (!isError) {
            cout << "        SUCCESS Get works good" << endl;
        }
    }

    void TestContains() {
        cout << "    Is contain Cat in BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        auto cat = catsArray->Get(0);
        auto hasCatInTree = catTree->Contains(cat);

        bool isError = false;

        if (!hasCatInTree) {
            isError = true;

            cout << "        ERROR Cat contains" << endl;
        }

        auto newCat = Cat("Nika", 111);
        hasCatInTree = catTree->Contains(newCat);

        if (hasCatInTree) {
            isError = true;

            cout << "        ERROR New cat doesn't contains" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Contains works good" << endl;
        }
    }

    void TestAdd() {
        cout << "    Adding Cat in BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        auto newCat1 = Cat("Nika", 111);
        auto newCat2 = Cat("Nika", 6);

        catTree->Add(newCat1);
        catTree->Add(newCat2);

        bool isError = false;

        if (!catTree->Contains(newCat1) || !catTree->Contains(newCat2)) { 
            isError = true;

            cout << "        ERROR Addition works bad" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Addition works good" << endl;
        }
    }

    void TestRemove() {
        cout << "    Removing Cat in BinarySearchTree<Cat>" << endl;

        auto catsArray = getCatsArray();
        auto catTreeBuilder = BinaryTreeBuilder<Cat>();
        auto catTree = catTreeBuilder.FromSequence(catsArray);

        bool isError = false;

        auto cat = catsArray->Get(5);
        catTree->Remove(cat);

        if (catTree->Contains(cat)) { 
            isError = true;

            cout << "        ERROR Removing works bad" << endl;
        }

        catTree = catTreeBuilder.FromSequence(catsArray);

        cat = catsArray->Get(6);
        catTree->Remove(cat);

        if (catTree->Contains(cat)) { 
            isError = true;

            cout << "        ERROR Removing works bad" << endl;
        }

        catTree = catTreeBuilder.FromSequence(catsArray);

        cat = catsArray->Get(0);
        catTree->Remove(cat);

        if (catTree->Contains(cat)) { 
            isError = true;

            cout << "        ERROR Removing works bad" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Removing works good" << endl;
        }
    }
};
