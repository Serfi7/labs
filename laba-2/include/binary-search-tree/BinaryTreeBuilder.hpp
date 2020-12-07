#pragma once

#include "./BinarySearchTree.hpp"

#include "../../test/Mock.hpp"

template<class T>
class BinaryTreeBuilder {
public:
    BinaryTreeBuilder();

    BinarySearchTree<T>* FromSequence(Sequence<T>* sequence);
};

template<class T>
BinaryTreeBuilder<T>::BinaryTreeBuilder() {}

template<class T>
BinarySearchTree<T>* BinaryTreeBuilder<T>::FromSequence(Sequence<T>* sequence) {
    BinarySearchTree<T>* tree = new BinarySearchTree<T>();

    int sequenceLength = sequence->GetLength();
    for (int i = 0; i < sequenceLength; i++) {
        tree->Add(sequence->Get(i));
    }

    return tree;
}
