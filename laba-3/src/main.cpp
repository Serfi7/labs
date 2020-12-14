#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "../test/Mock.hpp"
#include "../include/array/ArraySequence.hpp"

#include "../include/graph/Graph.hpp"
#include "../include/graph/NodesElement.hpp"

using namespace std;
using namespace Mock;

void joinSequence(Sequence<PathInfo<int>*>* pathInfo) {
    cout << "Prev node: ";
    for (int i = 0; i < pathInfo->GetLength(); i++) {
        cout << i << ": " << pathInfo->Get(i)->PrevNode() << ", ";
    }
    cout << endl;

    cout << "Min path: ";
    for (int i = 0; i < pathInfo->GetLength(); i++) {
        cout << i << ": " << pathInfo->Get(i)->Path() << ", ";
    }
    cout << endl;
}

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

int main() {
    // auto pair01 = new NodesElement<int>(0, 1, 40);
    // auto pair04 = new NodesElement<int>(0, 4, 18);

    // auto pair12 = new NodesElement<int>(1, 2, 22);
    // auto pair13 = new NodesElement<int>(1, 3, 6);
    // auto pair14 = new NodesElement<int>(1, 4, 15);

    // auto pair23 = new NodesElement<int>(2, 3, 14);

    // auto pair34 = new NodesElement<int>(3, 4, 20);

    // auto nodes = new ArraySequence<NodesElement<int>*>();

    // nodes->Append(pair01);
    // nodes->Append(pair04);

    // nodes->Append(pair12);
    // nodes->Append(pair13);
    // nodes->Append(pair14);

    // nodes->Append(pair23);

    // nodes->Append(pair34);

    //auto graph = new Graph<int>(nodes, 5, false);

    //cout << graph->JoinAdjacencyMatrix() << endl;

    auto newPair02 = new NodesElement<int>(0, 2, 6);
    auto newPair03 = new NodesElement<int>(0, 3, 122);
    auto newPair04 = new NodesElement<int>(0, 4, 25);

    auto newPair10 = new NodesElement<int>(1, 0, 34);
    auto newPair14 = new NodesElement<int>(1, 4, 37);

    auto newPair20 = new NodesElement<int>(2, 0, 7);
    auto newPair21 = new NodesElement<int>(2, 1, 23);

    auto newPair31 = new NodesElement<int>(3, 1, 29);

    auto newPair42 = new NodesElement<int>(4, 2, 11);

    auto newNodes = new ArraySequence<NodesElement<int>*>();

    newNodes->Append(newPair02);
    newNodes->Append(newPair03);
    newNodes->Append(newPair04);

    newNodes->Append(newPair10);
    newNodes->Append(newPair14);

    newNodes->Append(newPair20);
    newNodes->Append(newPair21);

    newNodes->Append(newPair31);

    newNodes->Append(newPair42);

    auto directedGraph = new Graph<int>(newNodes, 5);

    cout << "Directed graph:" << endl;
    cout << directedGraph->JoinAdjacencyMatrix() << endl;

    auto pair01 = new NodesElement<int>(0, 1, 10);
    auto pair02 = new NodesElement<int>(0, 2, 30);
    auto pair03 = new NodesElement<int>(0, 3, 50);
    auto pair04 = new NodesElement<int>(0, 4, 10);

    auto pair24 = new NodesElement<int>(2, 4, 10);

    auto pair31 = new NodesElement<int>(3, 1, 40);
    auto pair32 = new NodesElement<int>(3, 2, 20);

    auto pair40 = new NodesElement<int>(4, 0, 10);
    auto pair42 = new NodesElement<int>(4, 2, 10);
    auto pair43 = new NodesElement<int>(4, 3, 30);

    auto nodes = new ArraySequence<NodesElement<int>*>();

    nodes->Append(pair01);
    nodes->Append(pair02);
    nodes->Append(pair03);
    nodes->Append(pair04);

    nodes->Append(pair24);

    nodes->Append(pair31);
    nodes->Append(pair32);

    nodes->Append(pair40);
    nodes->Append(pair42);
    nodes->Append(pair43);

    auto graph = new Graph<int>(nodes, 5);

    cout << endl << "Indirected graph:" << endl;
    cout << graph->JoinAdjacencyMatrix() << endl;

    int fromNode = 0;
    auto nodesVector = graph->DijkstraAlgorithm(fromNode);

    cout << "Form " << fromNode << " node:" << endl;
    joinSequence(nodesVector);
    cout << endl;
    delete nodesVector;

    fromNode = 2;
    nodesVector = graph->DijkstraAlgorithm(fromNode);

    cout << "Form " << fromNode << " node:" << endl;
    joinSequence(nodesVector);
    cout << endl;
    delete nodesVector;

    fromNode = 1;
    nodesVector = graph->DijkstraAlgorithm(fromNode);

    cout << "Form " << fromNode << " node:" << endl;
    joinSequence(nodesVector);

    // while (1) {
    //     cout << "Enter command:" << endl;
    //     cout << "1) From file" << endl;
    //     cout << "0) Exit" << endl;
    //     cout << "Command: ";

    //     int command = -1;

    //     cin >> command;

    //     switch (command) {
    //         case 1:
    //             fromFile();
    //             break;
    //         case 3:
    //             return 0;
    //     }

    //     cin.clear();
    // }

    return 0;
}
