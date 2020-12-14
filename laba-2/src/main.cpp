#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "../test/Mock.hpp"
#include "../include/array/ArraySequence.hpp"
#include "../include/binary-search-tree/BinaryTreeBuilder.hpp"

#include "../include/histogram/Histogram.hpp"
#include "../include/histogram/HistogramBuilder.hpp"

using namespace std;
using namespace Mock;

void joinSequence(Sequence<int>* nums) {
    for (int i = 0; i < nums->GetLength() - 1; i++) {
        cout << nums->Get(i) << ", ";
    }

    cout << nums->Get(nums->GetLength() - 1) << endl;
}

void joinSequence(Sequence<string>* strs) {
    for (int i = 0; i < strs->GetLength() - 1; i++) {
        cout << strs->Get(i) << ", ";
    }

    cout << strs->Get(strs->GetLength() - 1) << endl;
}

void joinSequence(Sequence<Cat>* cats) {
    for (int i = 0; i < cats->GetLength(); i++) {
        cout << cats->Get(i).name << " " << cats->Get(i).age << ", " << endl;
    }
}

vector<int> readNumsFromFile() {
    vector<int> data;

    ifstream file("input.txt");

    if (!file.good()) {
        return data;
    }

    int number;

    while (file >> number) {
        data.push_back(number);
    }

    file.close();

    return data;
}

ArraySequence<string>* readNames(ifstream &file) {
    auto names = new ArraySequence<string>();

    string namesLine;
    getline(file, namesLine);

    istringstream iss(namesLine);
    string name;
    while (iss >> name) {
        names->Append(name);
    }

    return names;
}

ArraySequence<Cat>* readCats(ifstream &file) {
    ArraySequence<Cat>* cats = new ArraySequence<Cat>();

    string catLine;
    while (getline(file, catLine)) {
        istringstream iss(catLine);
        string name;
        int age;

        iss >> name >> age;

        auto cat = Cat(name, age);
        cats->Append(cat);
    }

    return cats;
}

Histogram<Cat, string>* namesHistogram(Sequence<Cat>* cats, Sequence<string>* names) {
    auto splitter = [](const Cat& cat) -> string {
        return cat.name;
    };

    auto histogramBuilder = HistogramBuilder<Cat, string>();
    auto histogram = histogramBuilder.HashDictionaryFromSequence(
        cats,
        names,
        splitter
    );

    return histogram;
}

void writeResultToFile(Sequence<int>* seq, double microseconds, string sortSort) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Sort: " << sortSort << endl;
    output << "Sequence length: " << seq->GetLength() << endl;
    output << "Sorting time: " << microseconds / 1000 << " ms" << endl;
    output << endl;
    output.close();
}

void writeNamesHistogram(Histogram<Cat, string>* histogram) {
    ofstream output("output.txt", ios::ios_base::app);

    if (!output.is_open()) {
        cout << "Could not open file. Try again." << endl;
    }

    output << "Histogram by names: " << endl;
    output << histogram->joinDevision("\n");
    output << endl;

    output.close();

    cout << "Histogram by names was successfully write to 'output.txt'" << endl;
    cout << "Histogram by ages was successfully write to 'output.txt'" << endl;
    cout << "Histogram by names:" << endl;
    cout << histogram->joinDevision("\n");
    cout << endl;
}

void fromFile() {
    ifstream file("input.txt");

    if (!file.good()) {
        cout << "Bad file. Back to menu" << endl;
        return;
    }

    auto namesRange = readNames(file);
    auto cats = readCats(file);

    file.close();

    auto histogramByNames = namesHistogram(cats, namesRange);

    writeNamesHistogram(histogramByNames);

    delete namesRange;
    delete cats;
    delete histogramByNames;
}

class BSTNode{
public:
    int value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) : value(value) {}
};

class BST {
public:
    BSTNode* root;

    BST() {}
};

bool isBST(BSTNode* node, int min, int max) {
    if (!node) {
        return true;
    }

    if (node->value < min || node->value > max) {
        return false;
    }

    return isBST(node->left, min, node->value) &&
        isBST(node->right, node->value, max);
}

bool isBST(BSTNode* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

int main() {
    // auto node1 = new BSTNode(5);
    // auto node2 = new BSTNode(9);
    //auto node3 = new BSTNode(3);
    // auto node4 = new BSTNode(4);
    // auto node5 = new BSTNode(2);
    //auto node6 = new BSTNode(7);

    // node1->left = node4;
    // node1->right = node2;

    //node2->left = node3;

    //node4->left = node5;

    //node5->right = node6;

    // auto bintree = new BST();
    // bintree->root = node1;

    //cout << (isBST(bintree->root) ? "BST" : "not BST") << endl;
    //notBST->Add(5);
    //notBST->Add(5);

    while (1) {
        cout << "Enter command:" << endl;
        cout << "1) From file" << endl;
        cout << "0) Exit" << endl;
        cout << "Command: ";

        int command = -1;

        cin >> command;

        switch (command) {
            case 1:
                fromFile();
                break;
            case 3:
                return 0;
        }

        cin.clear();
    }

    return 0;
}
