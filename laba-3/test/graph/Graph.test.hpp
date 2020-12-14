#pragma once

#include "iostream"

#include "../../include/array/ArraySequence.hpp"
#include "../Mock.hpp"

#include "../../include/graph/Graph.hpp"
#include "../../include/graph/NodesElement.hpp"

using namespace std;
using namespace Mock;

class ArraySequenceTest {
public:
    ArraySequenceTest() {
        TestCreatingGraph();
        cout << endl;
        TestDijakstraAlgarithm();
    }

private:
    void TestCreatingGraph() {
        cout << "    Creating Graph<int>" << endl;

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

        auto adjacencyMatrix = directedGraph->JoinAdjacencyMatrix();

        auto mockMatrix = "-1 0 6 122 25\n34 -1 0 0 37\n7 23 -1 0 0\n0 29 0 -1 0\n0 0 11 0 -1";

        bool isError = false;
        if (adjacencyMatrix !=mockMatrix) {
            cout << "        ERROR Graph created wrong" << endl;
        }

        if (!isError) {
            cout << "        SUCCESS Graph created successful" << endl;
        }
    }

    void TestDijakstraAlgarithm() {
        cout << "    Test DijkstraAlgorithm" << endl;

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

        int fromNode = 0;
        auto pathInfo = graph->DijkstraAlgorithm(fromNode);

        auto mockPrevNode = "0 0 4 4 0";
        auto mockPath = "0 10 20 40 10";

        std::string prevNodes = "";
        for (int i = 0; i < pathInfo->GetLength(); i++) {
            prevNodes += pathInfo->Get(i)->PrevNode();
        }

        std::string path = "";
        for (int i = 0; i < pathInfo->GetLength(); i++) {
            path += pathInfo->Get(i)->Path();
        }

        bool isError = false;
        if (prevNodes != mockPrevNode) {
            cout << "        ERROR Dijkstra Algorithm return bad prev nodes";

            isError = true;
        }

        if (path != mockPath) {
            cout << "        ERROR Dijkstra Algorithm return bad path";

            isError = true;
        }

        if (!isError) {
            cout << "        SUCCESS Dijkstra Algorithm works good" << endl;
        }
    }
};
