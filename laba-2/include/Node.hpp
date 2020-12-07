#pragma once

#include "./dictionary/Pair.hpp"
#include "../test/Mock.hpp"

using namespace Mock;

template<class T>
class Node {
public:
    Node<T>();
    Node<T>(const T& value);
    Node<T>(const Node<T>& node);

    T* value;
    Node<T>* left;
    Node<T>* right;
};

template<class T>
Node<T>::Node(const T& value) {
      this->value = new T(value);

      this->left = nullptr;
      this->right = nullptr;
}

template<class T>
Node<T>::Node(const Node<T>& node) {
      this->value = new T(*node.value);

      if (node.left) {
        this->left = new Node(*node.left);
      }

      if (node.right) {
        this->right = new Node(*node.right);
      }
}

template<class T>
Node<T>::Node() {
    this->value = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

//template<class T>
//Node<T>::~Node() {
    //delete this->value;
//}

