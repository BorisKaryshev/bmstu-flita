#include <iostream>
#include "Graph.h"

int main()
{
    Graph example;
    example.ReadFromFile("input.txt"); // in file rows are edges, colums are nodes

    example.ExportIntoDot();
    return 0;
}
