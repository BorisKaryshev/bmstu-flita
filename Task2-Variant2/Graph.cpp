#include "Graph.h"
#include <iostream>
#include <fstream>
#define DefaultNodsNumber 10

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

struct Edge** push(struct Edge** edges, struct Edge* new_edge, int number_of_edges) {
    struct Edge** temp = new struct Edge* [number_of_edges + 1];
    for (int i = 0; i < number_of_edges; temp[i] = edges[i++]);
    temp[number_of_edges] = new_edge;
    //delete[] edges;
    return temp;
}

int isConected(struct Node* from, struct Node* where) {
    for (int i = 0; i < from->number_of_edges; i++) 
        if ((from->edges[i]->from == from && from->edges[i]->where == where) || (from->edges[i]->from == where && from->edges[i]->where == from))
            return from->edges[i]->weight;
    return 0;
}

void Graph::PrintAdjacencyMatrix() {
    std::cout  << "  ";
    for (int i = 0; i < number_of_nodes; std::cout << nodes[i++].index << " ");
    std::cout << "\n";
    int x = 0;
    for (int i = 0; i < number_of_nodes; i++) {
        std::cout << nodes[i].index << " ";
        for (int j = 0; j < number_of_nodes; j++) {
            if ((x = isConected(&nodes[i], &nodes[j])) != 0)
                std::cout << x << " ";
            else
                std::cout << "_ ";
        }
        std::cout << '\n';
    }
}

void Graph::PrintEdges() {
    std::cout << "Number of edges = " << number_of_edges << "\n";
    for (int i = 0; i < number_of_edges; i++)
        std::cout << "edge " << i + 1 << " connected with " << edges[i]->from->index << " and " << edges[i]->where->index << ", weigth = " << edges[i]->weight << "\n";

    for (int i = 0; i < number_of_nodes; i++) {
        std::cout << "Node " << nodes[i].index << " has\n";
        for (int j = 0; j < nodes[i].number_of_edges; j++) {
            if (nodes[i].edges[j]->where == &nodes[i])
                std::cout << "\tedge with node " << nodes[i].edges[j]->from->index  << " it weigth is " << nodes[i].edges[j]->weight << "\n";
            else 
                std::cout << "\tedge with node " << nodes[i].edges[j]->where->index << " it weigth is " << nodes[i].edges[j]->weight << "\n";
        }
    }
}

void Graph::ReadFromFile(std::string file_name) {
    std::ifstream File(file_name, std::ios_base::in);
    int x = 0, yPos = 1;
    std::string line;
    std::getline(File, line);
    int* arr = new int[DefaultNodsNumber];
    int j = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            x *= 10;
            x += line[i] - '0';
        }
        else if (line[i] != ' ' && (line[i] < '0' || line[i] > '9'))
            std::cout << "ERROR: unknown symbol\n";
        else if ((line[i] == ' ' || line[i] == '\n') && x != 0) {
            if ((j+1) % 10 == 0 && j != 0) {
                int* temp = new int[DefaultNodsNumber * (j/10+1)];
                for (int k = 0; k < j; temp[k] = arr[k++]);
                //delete[] arr;
                arr = temp;
            }
            arr[j++] = x;
            x = 0;
            number_of_nodes++;
        }
    }
    arr[j++] = x;
    nodes = new struct Node[++number_of_nodes];
    for (int i = 0; i < number_of_nodes; i++) {
        nodes[i].index = arr[i];
        nodes[i].edges = NULL;
        nodes[i].number_of_edges = 0;
    }
    arr = new int[number_of_nodes];

    while (std::getline(File, line)) {
        struct Edge* tmp = new struct Edge;
        arr = strtoi(number_of_nodes, line);
        tmp->from = NULL;
        tmp->where = NULL;
        for (int i = 0; i < number_of_nodes; i++) {
            if (arr[i] > 0 && tmp->from == NULL) {
                tmp->from = &nodes[i];
                tmp->weight = arr[i];
                nodes[i].edges = push(nodes[i].edges, tmp, nodes[i].number_of_edges);
                nodes[i].number_of_edges++;
            }
            else if (arr[i] > 0 && tmp->where == NULL) {
                tmp->where = &nodes[i];
                tmp->weight = arr[i];
                nodes[i].edges = push(nodes[i].edges, tmp, nodes[i].number_of_edges);
                nodes[i].number_of_edges++;
            }

        }
        if (tmp->where == NULL)
            tmp->where = tmp->from;
        edges = push(edges, tmp, number_of_edges);
        number_of_edges++;
        tmp = NULL;
    }

    File.close();
}

void Graph::ExportIntoDot() {
    std::ofstream File("output.dot");
    File << "graph graphname {\n";
    for (int i = 0; i < number_of_nodes; File << "\t" << nodes[i++].index << ";\n");
    for (int i = 0; i < number_of_edges; i++)
        File << "\t" << edges[i]->from->index << " -- " << edges[i]->where->index << ";\n";
    File << "}";
    File.close();
}