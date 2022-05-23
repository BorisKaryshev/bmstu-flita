#pragma once
#include <string>

namespace MyGraph {
    struct Edge {
        int index;
        int node_from_index;
        int node_where_index;
    };

    struct Node {
        int index;
        std::string name;
        int* edges;
        int number_of_edges = 0;
    };
	
    class Graph {
	private:
        struct Node* nodes;
        struct Edge* edges;
        int number_of_nodes = 0;
        int number_of_edges = 0;
        bool IsNodesConnected(int node1_index, int node2_index);
        bool DoesPathExists(int start_index, int end_index, bool* where_was);

    public:
        Graph() :nodes(NULL), edges(NULL), number_of_edges(0), number_of_nodes(0) {};
        ~Graph() { delete[] nodes; delete[] edges; }

        void PushNode(struct Node node);
        void PushNode(std::string name);

        void PushEdge(int index_from, int index_where);

        void ReadFromFile(std::string file_name);
        int NumberOfEdges();
        int NumberOfNodes();

        void PrintAdjacencyMatrix();
        void PrintEdges();

        void ExportIntoDot();
        bool IsGraphConnected_Theorem();
        bool IsGraphConnected();
	};

}