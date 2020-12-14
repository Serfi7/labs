#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Node {
public:
    int value;
    vector<Node> children;

    Node()
        : value(0),
          children(vector<Node>()) {}

    Node(int value)
        : value(value),
          children(vector<Node>())
    {}
};

class NTree {
public:
    Node root;

    NTree() : root() {}
    NTree(Node root) : root(root) {}
};

NTree initTree() {
    Node aaaNode = Node(77);
    Node bbbNode = Node(88);
    Node cccNode = Node(1);
    Node dddNode = Node(7);
    Node eeeNode = Node(8);
    Node fffNode = Node(9);

    Node aaNode = Node(2);
    Node bbNode = Node(34);
    Node ccNode = Node(56);
    Node ddNode = Node(100);

    Node aNode = Node(10);


    aaNode.children.push_back(aaaNode);
    aaNode.children.push_back(bbbNode);

    ccNode.children.push_back(cccNode);

    ddNode.children.push_back(dddNode);
    ddNode.children.push_back(eeeNode);
    ddNode.children.push_back(fffNode);

    aNode.children.push_back(aaNode);
    aNode.children.push_back(bbNode);
    aNode.children.push_back(ccNode);
    aNode.children.push_back(ddNode);

    return NTree(aNode);
}

class NodesElement {
private:
    int from;
    int to;

public:
    NodesElement(int from, int to)
        : from(from),
          to(to)
    {}

    int From() {
        return from;
    }

    int To() {
        return to;
    }
};

class Graph {
public:
    vector<vector<int>> adjacencyMatrix;

    Graph(const vector<NodesElement> data, int nodeCount) {
        for (int i = 0; i < nodeCount; i++) {
            auto row = vector<int>();

            for (int j = 0; j < nodeCount; j++) {
                row.push_back(0);
            }

            adjacencyMatrix.push_back(row);
        }

        int pairCount = data.size();
        for (int i = 0; i < pairCount; i++) {
            auto pair = data[i];

            adjacencyMatrix[pair.From()][pair.To()] = 1;
            adjacencyMatrix[pair.To()][pair.From()] = 1;
        }
    }

    void join() {
        auto nodesCount = adjacencyMatrix.size();

        for (int i = 0; i < nodesCount - 1; i++) {
            auto row = adjacencyMatrix[i];

            for (int j = 0; j < nodesCount; j++) {
                cout << row[j] << " ";
            }

            cout << endl;
        }

        auto lastRow = adjacencyMatrix[nodesCount - 1];

        for (int j = 0; j < nodesCount; j++) {
            cout << lastRow[j] << " ";
        }
        cout << endl;
    }


    void _dfs(const int node, vector<bool> visitedNodes) {
        //cout << visitedNodes[node] << endl;
        if (visitedNodes[node]) {
            return;
        }

        cout << node << endl;

        visitedNodes[node] = true;

        auto adjacencyNodes = adjacencyMatrix[node];

        for (int i = 0; i < adjacencyNodes.size(); ++i) {
            if (adjacencyNodes[i] <= 0 || visitedNodes[i]) {
                continue;
            }

            _dfs(i, visitedNodes);
        }
    }

    void Dfs(const int node = 0) {
        auto visitedNodes = vector<bool>(adjacencyMatrix.size());

        _dfs(node, visitedNodes);
    }

    void _bfs(queue<int> nodes, vector<bool> visitedOrQueuedNodes) {
        if (nodes.empty()) {
            return;
        }

        queue<int> nextNodes;

        while (!nodes.empty()) {
            int currentNode = nodes.front();
            nodes.pop();

            cout << currentNode << " ";

            visitedOrQueuedNodes[currentNode] = true;

            auto adjacencyNodes = adjacencyMatrix[currentNode];
            for (int i = 0; i < adjacencyNodes.size(); i++) {
                if (adjacencyNodes[i] <= 0 || visitedOrQueuedNodes [i]) {
                    continue;
                }

                nextNodes.push(i);
                visitedOrQueuedNodes[i] = true;
            }
        }

        cout << endl;

        _bfs(nextNodes, visitedOrQueuedNodes);
    }

    void Bfs(const int node = 0) {
        auto visitedNodes = vector<bool>(adjacencyMatrix.size());

        auto nodes = queue<int>();
        nodes.push(node);

        _bfs(nodes, visitedNodes);
    }
};

void addToQueueChildren(queue<Node>& queue, Node root) {
    int childrenSize = root.children.size();

    for (int i = 0; i < childrenSize; i++) {
        queue.push(root.children[i]);
    }
}

void treeBfs(queue<Node> floor) {
    if (floor.empty()) {
        return;
    }

    queue<Node> nextFloor;

    while (!floor.empty()) {
        Node currentNode = floor.front();
        floor.pop();

        cout << currentNode.value << ' ';

        addToQueueChildren(nextFloor, currentNode);
    }

    cout << endl;

    treeBfs(nextFloor);

}

void treeBfs(Node root) {
    queue<Node> rootFloor;
    rootFloor.push(root);

    treeBfs(rootFloor);
}

void treeDfs(Node root) {
    cout << root.value << endl;
    int childrenSize = root.children.size();
    if (!childrenSize) {
        return;
    }

    queue<Node> children;

    for (int i = 0; i < childrenSize; i++) {
        treeDfs(root.children[i]);
    }
}

int main() {
    //NTree nTree = initTree();

    //cout << "bfs for tree:" << endl;
    //treeBfs(nTree.root);

    //cout << endl;

    //cout << "dfs for tree:" << endl;
    //treeDfs(nTree.root);

    auto pair01 = NodesElement(0, 1);
    auto pair02 = NodesElement(0, 2);

    auto pair24 = NodesElement(2, 4);

    auto pair31 = NodesElement(3, 1);
    auto pair32 = NodesElement(3, 2);

    auto pair42 = NodesElement(4, 2);
    auto pair43 = NodesElement(4, 3);

    auto nodes = vector<NodesElement>();

    nodes.push_back(pair01);
    nodes.push_back(pair02);

    nodes.push_back(pair24);

    nodes.push_back(pair31);
    nodes.push_back(pair32);

    nodes.push_back(pair42);
    nodes.push_back(pair43);

    auto graph = new Graph(nodes, 5);

    graph->join();
    //graph->Dfs(0);
    cout << "bfs" << endl;
    graph->Bfs(0);

    return 0;
};

