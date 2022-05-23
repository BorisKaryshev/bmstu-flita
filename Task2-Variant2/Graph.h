#pragma once
#include <string>

struct Edge {
    float weight;
    struct Node* from;
    struct Node* where;
};

struct Node {
    int index;
    struct Edge** edges;
    int number_of_edges = 0;
};

class Graph {
private:
    struct Node* nodes;
    struct Edge** edges;
    int number_of_nodes = 0;
    int number_of_edges = 0;
public:
    Graph() :nodes(NULL), edges(NULL) {};
    ~Graph() { };//delete[] nodes; }

    void ReadFromFile(std::string file_name);
    void PrintAdjacencyMatrix();
    void PrintEdges();
    void ExportIntoDot();
};