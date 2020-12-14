#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "./include/array/ArraySequence.hpp"
#include "./include/graph/Graph.hpp"

using namespace std;

const int fieldSize = 5;

struct Point {
    int x;
    int y;

    Point(int x, int y): x(x), y(y) {}
};

const Point start = Point(1, 1);
const Point finish = Point(3, 4);

vector<int> row1() {
    auto row = vector<int>();

    row.push_back(3);
    row.push_back(0);
    row.push_back(0);
    row.push_back(0);
    row.push_back(0);

    return row;
}

vector<int> row2() {
    auto row = vector<int>();

    row.push_back(0);
    row.push_back(1);
    row.push_back(3);
    row.push_back(0);
    row.push_back(3);

    return row;
}

vector<int> row3() {
    auto row = vector<int>();

    row.push_back(0);
    row.push_back(3);
    row.push_back(3);
    row.push_back(0);
    row.push_back(0);

    return row;
}

vector<int> row4() {
    auto row = vector<int>();

    row.push_back(0);
    row.push_back(0);
    row.push_back(3);
    row.push_back(3);
    row.push_back(2);

    return row;
}

vector<int> row5() {
    auto row = vector<int>();

    row.push_back(0);
    row.push_back(0);
    row.push_back(0);
    row.push_back(0);
    row.push_back(3);

    return row;
}

vector<vector<int>> initField() {
    vector<vector<int>> field;

    field.push_back(row1());
    field.push_back(row2());
    field.push_back(row3());
    field.push_back(row4());
    field.push_back(row5());

    return field;
}

void renderField() {
    auto field = initField();

    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

Graph<int>* initFieldGraph() {
    auto field = initField();

    auto nodes = new ArraySequence<NodesElement<int>*>();

    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            auto currentCell = field[i][j];

            auto currentNodeIndex = i * 5 + j;

            if (j < fieldSize - 1) {
                auto weight = 1;

                if (i != 0) {
                    auto leftTopCell = field[i - 1][j + 1];
                    if (currentCell == 3 || leftTopCell == 3) {
                        weight = 0;
                    }

                    auto leftTopNodeIndex = 5 * (i - 1) + j + 1;


                    auto node = new NodesElement<int>(currentNodeIndex, leftTopNodeIndex, weight);
                    nodes->Append(node);
                }

                weight = 1;
                auto leftCell = field[i][j + 1];
                if (currentCell == 3 || leftCell == 3) {
                    weight = 0;
                }

                auto leftNodeIndex = currentNodeIndex + 1;
                auto node = new NodesElement<int>(currentNodeIndex, leftNodeIndex, weight);
                nodes->Append(node);

                if (i < fieldSize - 1) {
                    weight = 1;
                    auto leftBottomCell = field[i + 1][j + 1];
                    if (currentCell == 3 || leftCell == 3) {
                        weight = 0;
                    }

                    auto leftBottomNodeIndex = 5 * (i + 1) + j + 1;
                    auto node = new NodesElement<int>(currentNodeIndex, leftBottomNodeIndex, weight);
                    nodes->Append(node);

                    weight = 1;
                    auto bottomCell = field[i + 1][j];
                    if (currentCell == 3 || bottomCell == 3) {
                        weight = 0;
                    }

                    auto bottomNodeIndex = 5 * (i + 1) + j;
                    node = new NodesElement<int>(currentNodeIndex, bottomNodeIndex, weight);
                    nodes->Append(node);

                    if (j > 0) {
                        weight = 1;
                        auto leftBottomCell = field[i + 1][j - 1];
                        if (currentCell == 3 | leftBottomCell == 3) {
                            weight = 0;
                        }

                        auto bottomLeftIndex = 5 * (i + 1) + j - 1;
                        node = new NodesElement<int>(currentNodeIndex, bottomLeftIndex, weight);
                        nodes->Append(node);
                    }
                }
            }
        }
    }

    return new Graph<int>(nodes, 25);
}

void writePath(Sequence<PathInfo<int>*>* pathInfo, int indexOfStart, int indexOfEnd) {
    auto prevNode = pathInfo->Get(indexOfEnd)->PrevNode();

    if (prevNode == -1) {
        cout << "Unreachable cell" << endl;
        return;
    }

    while (prevNode != indexOfStart) {
        auto nodeY = prevNode % fieldSize;
        auto nodeX = (prevNode - nodeY ) / 5;
        cout << prevNode << " node (x: " << nodeX << ", y: " << nodeY << ")" << endl;

        prevNode = pathInfo->Get(prevNode)->PrevNode();
    }
}

int main() {
    renderField();
    auto graphOfField = initFieldGraph();

    auto indexOfStart = start.x * 5 + start.y;
    auto indexOfEnd = finish.x * 5 + finish.y;

    auto pathInfo = graphOfField->DijkstraAlgorithm(indexOfStart);

    cout << "From " << indexOfStart << " node (x: " << start.x << ", y: " << start.y << ")" << endl;
    cout << "To " << indexOfEnd << " node (x: " << finish.x << ", y: " << finish.y << ")" << endl;
    cout << "Min distance: " << pathInfo->Get(indexOfEnd)->Path() << " steps" << endl;
    writePath(pathInfo, indexOfStart, indexOfEnd);

    return 0;
};

