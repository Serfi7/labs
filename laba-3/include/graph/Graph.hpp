#pragma once

#include "../Sequence.hpp"
#include "../array/ArraySequence.hpp"

#include "./NodesElement.hpp"

template<class TArc>
class PathInfo {
private:
    int prevNode;
    TArc path;

public:
    PathInfo(int prevNode, TArc path) 
        : prevNode(prevNode),
          path(path) {}

    int PrevNode() {
        return prevNode;
    }

    TArc Path() {
        return path;
    }
};

template<class TArc>
class Graph {
private:
    Sequence<ArraySequence<TArc>*>* adjacencyMatrix;

    Sequence<PathInfo<TArc>*>* _dijkstraAlgorithm(Sequence<PathInfo<TArc>*>* nodesVector, Sequence<TArc>* marks, Sequence<bool>* visitedNodes);

public:
    Graph(const Sequence<NodesElement<TArc>*>* data, int nodeCount, bool isDirected = true);

    Sequence<PathInfo<TArc>*>* DijkstraAlgorithm(const int nodeIndex);

    std::string JoinAdjacencyMatrix(const std::string rowSeparator = "\n");
};

template<class TArc>
Graph<TArc>::Graph(const Sequence<NodesElement<TArc>*>* data, int nodeCount, bool isDirected) {
    adjacencyMatrix = new ArraySequence<ArraySequence<TArc>*>();

    for (int i = 0; i < nodeCount; i++) {
        auto row = new ArraySequence<TArc>();

        for (int j = 0; j < nodeCount; j++) {
            row->Append(i == j ? -1 : 0);
        }

        adjacencyMatrix->Append(row);
    }

    int pairCount = data->GetLength();
    for (int i = 0; i < pairCount; i++) {
        auto pair = data->Get(i);

        adjacencyMatrix
            ->Get(pair->From())
            ->Set(pair->Weight(), pair->To());

        if (isDirected) {
            continue;
        }

        adjacencyMatrix
            ->Get(pair->To())
            ->Set(pair->Weight(), pair->From());
    }
};

template<class TArc>
Sequence<PathInfo<TArc>*>* Graph<TArc>::_dijkstraAlgorithm(
        Sequence<PathInfo<TArc>*>* nodesVector,
        Sequence<TArc>* marks,
        Sequence<bool>* visitedNodes
    ) {
    int nodeCount = adjacencyMatrix->GetLength();

    int minNode = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (visitedNodes->Get(i)) {
            continue;
        }

        minNode = i;
        break;
    }

    if (minNode == -1) {
        return nodesVector;
    }

    int minMark = marks->Get(minNode);

    for (int i = 0; i < nodeCount; i++) {
        if (visitedNodes->Get(i)) {
            continue;
        }

        if (marks->Get(i) < minMark) {
            minNode = i;
            minMark = marks->Get(i);
        }
    }

    auto currentRow = adjacencyMatrix->Get(minNode);

    for (int i = 0; i < nodeCount; i++) {
        auto weightFromMinNode = currentRow->Get(i);

        if (weightFromMinNode <= 0) {
            continue;
        }

        auto newMark = minMark + weightFromMinNode;
        if (0 < newMark && newMark < marks->Get(i)) {
            marks->Set(newMark, i);

            auto newPathInfo = new PathInfo<TArc>(minNode, newMark);
            nodesVector->Set(newPathInfo, i);
        }
    }

    visitedNodes->Set(true, minNode);

    return _dijkstraAlgorithm(nodesVector, marks, visitedNodes);
}

template<class TArc>
Sequence<PathInfo<TArc>*>* Graph<TArc>::DijkstraAlgorithm(const int nodeIndex) {

    auto nodesCount = adjacencyMatrix->GetLength();

    auto nodesVector = new ArraySequence<PathInfo<TArc>*>();
    for (int i = 0; i < nodesCount; i++) {
        auto pathInfo = new PathInfo<TArc>(-1, -1);

        nodesVector->Append(pathInfo);
    }
    auto currentPathInfo = new PathInfo<TArc>(nodeIndex, 0);
    nodesVector->Set(currentPathInfo, nodeIndex);

    auto nodesMark = new ArraySequence<int>();
    for (int i = 0; i < nodesCount; i++) {
        nodesMark->Append(i == nodeIndex ? 0 : INT_MAX);
    }

    auto visitedNodes = new ArraySequence<bool>();
    for (int i= 0; i < nodesCount; i++) {
        visitedNodes->Append(false);
    }

    return _dijkstraAlgorithm(nodesVector, nodesMark, visitedNodes);
}

template<class TArc>
std::string Graph<TArc>::JoinAdjacencyMatrix(const std::string rowSeparator) {
    auto nodesCount = adjacencyMatrix->GetLength();

    std::stringstream out;

    for (int i = 0; i < nodesCount - 1; i++) {
        auto row = adjacencyMatrix->Get(i);

        for (int j = 0; j < nodesCount; j++) {
            out << row->Get(j) << " ";
        }

        out << rowSeparator;
    }

    auto lastRow = adjacencyMatrix->Get(nodesCount - 1);

    for (int j = 0; j < nodesCount; j++) {
        out << lastRow->Get(j) << " ";
    }

    return out.str();
};
