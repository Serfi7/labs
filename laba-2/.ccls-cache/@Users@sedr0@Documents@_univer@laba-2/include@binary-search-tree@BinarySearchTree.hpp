#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <functional>

#include "../Node.hpp"
#include "../Exception.hpp"

#include "../../test/Mock.hpp"
#include "../dictionary/Pair.hpp"
using namespace Mock;

template <class T>
class BinarySearchTree{
public:
    Node<T>* root;

    void _dfs(Node<T>* node, std::function<void (Node<T>*)>, std::string type = "SLR");
    const Node<T>* _binSearch(const Node<T>* node, const T& value);
    Node<T>* _binSearch(Node<T>* node, const T& value);
    void _add(Node<T>* node, const T& value);

    Node<T>* _remove(Node<T>* node, const T& value);
    const Node<T>* _minNode(const Node<T>* node);

    static void _deleteNodeCallback(Node<T>* node);

public:
    BinarySearchTree();
    BinarySearchTree(BinarySearchTree<T> &tree);
    ~BinarySearchTree();

    int GetCount();

    T Get(const T& value);
    void Set(const T value);
    bool Contains(const T& value);
    void Add(const T& value);
    void Remove(const T& value);

    std::string Join(std::string splitter = ", ");
};

template<class T>
BinarySearchTree<T>::BinarySearchTree() {
    root = nullptr;
}

template<class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T> &tree) {
    auto treeRoot = tree.root;

    this->root = new Node<T>(*treeRoot);
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    auto deleteNodeCallback = [](Node<T>* node) -> void {
        delete node;
    };

    _dfs(root, deleteNodeCallback);
}

template<class T>
void BinarySearchTree<T>::_deleteNodeCallback(Node<T>* node) {
    delete node;
}

template<class T>
void BinarySearchTree<T>::_dfs(
        Node<T>* node,
        std::function<void (Node<T>* node)> cb,
        std::string type) {
    if (!node) {
        return;
    }

    // save nodes for deletion case
    Node<T>* left = node->left;
    Node<T>* right = node->right;

    if (type == "SLR") {
        cb(node);
    }

    if (left) {
        _dfs(left, cb);
    }

    if (type == "LSR") {
        cb(node);
    }

    if (right) {
        _dfs(right, cb);
    }

    if (type == "LRS") {
        cb(node);
    }
}

template<class T>
const Node<T>* BinarySearchTree<T>::_binSearch(const Node<T>* node, const T& value) {
    if (!node) {
        return nullptr;
    }

    if (value < *node->value) {
        return _binSearch(node->left, value);
    }

    if (value > *node->value) {
        return _binSearch(node->right, value);
    }

    return node;
}

template<class T>
Node<T>* BinarySearchTree<T>::_binSearch(Node<T>* node, const T& value) {
    if (!node) {
        return nullptr;
    }

    if (value < *node->value) {
        return _binSearch(node->left, value);
    }

    if (value > *node->value) {
        return _binSearch(node->right, value);
    }

    return node;
}

template<class T>
void BinarySearchTree<T>::_add(Node<T>* node, const T& value) {
    if (value < *node->value) {
        if (node->left) {
            return _add(node->left, value);
        }

        node->left = new Node<T>(value);
        return;
    }

    if (node->right) {
        return _add(node->right, value);
    }

    node->right = new Node<T>(value);
    return;
}

template<class T>
const Node<T>* BinarySearchTree<T>::_minNode(const Node<T>* node) {
    while (node->left) {
        return _minNode(node->left);
    }

    return node;
}

template<class T>
Node<T>* BinarySearchTree<T>::_remove(Node<T>* node, const T& value) {
    if (!node) {
        throw new Exception("Not existed node");
    }

    if (value < *node->value) {
         node->left = _remove(node->left, value);
         return node;
    }

    if (value > *node->value) {
        node->right = _remove(node->right, value);
        return node;
    }

    if (!node->left) {
        Node<T>* temp = node->right;
        delete node;
        return temp;
    }

    if (!node->right) {
        Node<T>* temp = node->left;
        delete node;
        return temp;
    }

    const Node<T>* temp = _minNode(node->right);
    if (root == node) {
    }

    node->value = temp->value;
    node->right = _remove(node->right, *temp->value);
    return node;
}

template<class T>
int BinarySearchTree<T>::GetCount() {
    int count = 0;

    auto countNodes = [&count](Node<T>* node) -> void{
        count++;
    };

    _dfs(root, countNodes);

    return count;
}

template<class T>
T BinarySearchTree<T>::Get(const T& value) {
    const Node<T>* result = _binSearch(root, value);

    return *result->value;
}

template<class T>
void BinarySearchTree<T>::Set(T value) {
    Node<T>* result = _binSearch(root, value);

    if (!result) {
        return;
    }

    delete result->value;
    result->value = new T(value);
}

template<class T>
bool BinarySearchTree<T>::Contains(const T& value) {
    if (!root) {
        return false;
    }

    auto result = _binSearch(root, value);

    return result ? true : false;
}

template<class T>
void BinarySearchTree<T>::Add(const T& value) {
    if (root) {
        _add(root, value);
        return;
    }

    root = new Node<T>(value);
}

template<class T>
void BinarySearchTree<T>::Remove(const T& value) {
    root = _remove(root, value);
}

template<class T>
std::string BinarySearchTree<T>::Join(std::string splitter) {
    std::stringstream out;

    auto toString = [&out, splitter](Node<T>* node) -> void {
        out << *node->value;

        if (splitter.length() > 0) {
            out << splitter;
        }
    };

    _dfs(root, toString, "LSR");

    return out.str();
}
