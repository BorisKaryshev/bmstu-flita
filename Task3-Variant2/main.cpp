#include <iostream>
#include "MyGraph.h"

int main()
{
    MyGraph::Graph example;
    example.ReadFromFile("input.txt");
    example.ExportIntoDot();

    std::cout << "THEOREM: ";
    if (example.IsGraphConnected_Theorem())
        std::cout << "Graph is connected\n";
    else
        std::cout << "Graph is NOT connected\n";

    if (example.IsGraphConnected())
        std::cout << "Graph is connected\n";
    else
        std::cout << "Graph is NOT connected\n";

    return 0;
} 