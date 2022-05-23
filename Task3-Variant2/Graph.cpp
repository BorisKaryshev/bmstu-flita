#include "MyGraph.h"
#include <iostream>
#include <fstream>
#define DefaultNodsNumber 10

namespace MyGraph {
    int* strtoi(int size, std::string line) {
        int* arr = new int[size];
        int x = 0, pos = 0;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                x *= 10;
                x += line[i] - '0';
            }
            else if (line[i] != ' ' && (line[i] < '0' || line[i] > '9'))
                std::cout << "ERROR: unknown symbol\n";
            else {
                arr[pos++] = x;
                x = 0;
            }
            arr[pos] = x;
        }
        return arr;
    }



    bool Graph::IsNodesConnected(int node1_index, int node2_index) {
        for (int i = 0; i < nodes[node1_index].number_of_edges; i++) {
            if (edges[nodes[node1_index].edges[i]].node_from_index == node2_index && edges[nodes[node1_index].edges[i]].node_where_index == node1_index)
                return true;
            if (edges[nodes[node1_index].edges[i]].node_from_index == node1_index && edges[nodes[node1_index].edges[i]].node_where_index == node2_index)
                return true;
        }
        return false;
    }

    bool Graph::DoesPathExists(int start_index, int end_index, bool* where_was) {
        where_was[start_index] = true;

        for (int i = 0; i < nodes[start_index].number_of_edges; i++) {

            int new_start = start_index;
            if (edges[nodes[start_index].edges[i]].node_from_index == start_index)
                new_start = edges[nodes[start_index].edges[i]].node_where_index;
            else if (edges[nodes[start_index].edges[i]].node_where_index == start_index)
                new_start = edges[nodes[start_index].edges[i]].node_from_index;

            if (!where_was[new_start])
                if (new_start == end_index || DoesPathExists(new_start, end_index, where_was)) {
                    where_was[start_index] = false;
                    return true;
                }
        }

        where_was[start_index] = false;
        return false;
    }

    void Graph::PrintAdjacencyMatrix() {
        std::cout << "  ";
        for (int i = 0; i < number_of_nodes; std::cout << nodes[i++].name << " ");
        std::cout << "\n";
        int x = 0;
        for (int i = 0; i < number_of_nodes; i++) {
            std::cout << nodes[i].name << " ";
            for (int j = 0; j < number_of_nodes; j++) {
                if (IsNodesConnected(i, j))
                    std::cout << 1 << " ";
                else
                    std::cout << "_ ";
            }
            std::cout << '\n';
        }
    }

    void Graph::PrintEdges() {
        
        std::cout << "Number of edges = " << number_of_edges << "\n";
        for (int i = 0; i < number_of_edges; i++)
            std::cout << "edge " << i << " connected with " << nodes[edges[i].node_from_index].name << " and " << nodes[edges[i].node_where_index].name << "\n";

        for (int i = 0; i < number_of_nodes; i++) {
            std::cout << "Node " << nodes[i].name << " has\n";
            for (int j = 0; j < nodes[i].number_of_edges; j++) {
                if (edges[nodes[i].edges[j]].node_from_index == i)
                    std::cout << "\tedge with node " << nodes[edges[nodes[i].edges[j]].node_where_index].name << "\n";
                else
                    std::cout << "\tedge with node " << nodes[edges[nodes[i].edges[j]].node_from_index].name << "\n";
            }
        }
    }

    void Graph::ReadFromFile(std::string file_name) {
        std::ifstream File(file_name, std::ios_base::in);
        int x = 0, yPos = 1;

        std::string line;
        char name[1001];
        std::getline(File, line);
        int* arr = new int[DefaultNodsNumber];
        int j = 0, k = 0;
        for (int i = 0; i <= line.length(); i++) {
            if (line[i] != ' ' && line[i] != '\n' && line[i] != EOF) {
                name[j++] = line[i];
            }
            else {
                name[j] = '\0';
                j = 0;
                PushNode(name);
            }
                
        }
        name[j] = '\0';
        PushNode(name);

        while (std::getline(File, line)) {
            int* arr = strtoi(number_of_nodes, line);
            int node_from_index = -1;
            int node_where_index = -1;
            for (int i = 0; i < number_of_nodes; i++) {
                if (arr[i] > 0 && node_from_index == -1)
                    node_from_index = i;
                else if (arr[i] > 0 && node_where_index == -1) {
                    node_where_index = i;
                    break;
                }
            }

            if (node_where_index == -1)
                node_where_index = node_from_index;
            if (node_from_index != -1)
                PushEdge(node_from_index, node_where_index);
        }

        File.close();
    }

    void Graph::ExportIntoDot() {
        std::ofstream File("output.dot");
        File << "graph graphname {\n";
        for (int i = 0; i < number_of_nodes; File << "\t\"" << nodes[i++].name << "\"\n");
        for (int i = 0; i < number_of_edges; i++)
            File << "\t\"" << nodes[edges[i].node_from_index].name<< "\" -- " << nodes[edges[i].node_where_index].name << ";\n";
        File << "}";
        File.close();
    }

    int Graph::NumberOfEdges() {
        return number_of_edges;
    }

    int Graph::NumberOfNodes() {
        return number_of_nodes;
    }

    void Graph::PushNode(struct Node node) {
        struct Node* temp = new struct Node[++number_of_nodes];
        for (int i = 0; i < number_of_nodes - 1; i++) {
            temp[i].index = nodes[i].index;
            temp[i].edges = nodes[i].edges;
            temp[i].number_of_edges = nodes[i].number_of_edges;
        }
        temp[number_of_nodes - 1].index = node.index;
        temp[number_of_nodes - 1].edges = node.edges;
        temp[number_of_nodes - 1].number_of_edges = node.number_of_edges;

        delete[] nodes;
        nodes = temp;
    }

    void Graph::PushNode(std::string name) {
        struct Node* temp = new struct Node[++number_of_nodes];
        for (int i = 0; i < number_of_nodes - 1; i++) {
            temp[i].index = nodes[i].index;
            temp[i].edges = nodes[i].edges;
            temp[i].number_of_edges = nodes[i].number_of_edges;
            temp[i].name = nodes[i].name;
        }
        temp[number_of_nodes - 1].name = name;
        temp[number_of_nodes - 1].index = number_of_nodes-1;
        temp[number_of_nodes - 1].edges = NULL;
        temp[number_of_nodes - 1].number_of_edges = 0;
        delete[] nodes;
        nodes = temp;
    }

    void Graph::PushEdge(int index_from, int index_where) {
        struct Edge* temp = new struct Edge[++number_of_edges];
        for (int i = 0; i < number_of_edges - 1; temp[i] = edges[i++]);
        temp[number_of_edges - 1].index = number_of_edges - 1;
        temp[number_of_edges - 1].node_from_index = index_from;
        temp[number_of_edges - 1].node_where_index = index_where;
        delete[] edges;
        edges = temp;
        
        int* tmp = new int[++nodes[index_from].number_of_edges];
        for (int i = 0; i < nodes[index_from].number_of_edges - 1; tmp[i] = nodes[index_from].edges[i++]);
        tmp[nodes[index_from].number_of_edges - 1] = number_of_edges - 1;

        delete[] nodes[index_from].edges;
        nodes[index_from].edges = tmp;
        if (index_from == index_where)
            return;

        tmp = new int[++nodes[index_where].number_of_edges];
        for (int i = 0; i < nodes[index_where].number_of_edges - 1; tmp[i] = nodes[index_where].edges[i++]);
        tmp[nodes[index_where].number_of_edges - 1] = number_of_edges - 1;
        delete[] nodes[index_where].edges;
        nodes[index_where].edges = tmp;
    }

    bool Graph::IsGraphConnected() {
        bool* where_was = new bool[number_of_nodes];
        for (int i = 0; i < number_of_nodes; where_was[i++] = false);
        bool answer = false;

        for (int i = 1; i < number_of_nodes; i++)
            if (!DoesPathExists(0, i, where_was)) {
                std::cout << "Node " << nodes[0].name << " and " << nodes[i].name << " are not connected\n";
                return false;
            }

        return true;
    }

    bool Graph::IsGraphConnected_Theorem() {
        int edges_count = 0;
        
        for (int i = 0; i < number_of_edges; i++) {
            bool is_unique = true;
            if (edges[i].node_from_index == edges[i].node_where_index)
                is_unique = false;
            for (int j = 0; j < i && is_unique; j++){
                    bool edges_is_equal = edges[i].node_from_index == edges[j].node_from_index && edges[i].node_where_index == edges[j].node_where_index;
                    edges_is_equal = edges_is_equal || (edges[i].node_from_index == edges[j].node_where_index && edges[i].node_where_index == edges[j].node_from_index);
                    if (i != j && edges_is_equal)
                        is_unique = false;
                }
            if (is_unique)
                edges_count++;
        }
        if (2 * edges_count > (number_of_nodes - 1) * (number_of_nodes - 2))
            return true;
        return false;
    }
}