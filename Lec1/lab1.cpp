#include <iostream>
#include <vector>
#include <list>

const int rows = 7, cols = 7;

std::string values[7][7] = {
    {"0",  "n1", "n2", "n3", "n4", "n5", "n6"},
    {"n1", "0",  "10", "0",  "0",  "8",  "5"},
    {"n2", "10", "0",  "0",  "20", "12", "0"},
    {"n3", "0",  "0",  "0",  "4",  "0",  "0"},
    {"n4", "0",  "20", "4",  "0",  "15", "0"},
    {"n5", "8",  "12", "0",  "15", "0",  "7"},
    {"n6", "5",  "0",  "0",  "0",  "7",  "0"}
};

void printAdjacencyList() {
    const int vertices = 6;
    std::vector<char> vertexNames = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<std::list<int>> adjList(vertices);
    
    adjList[0] = {1, 2};       // A -> B, C
    adjList[1] = {0, 2, 3, 5}; // B -> A, C, D, F
    adjList[2] = {0, 1};       // C -> A, B
    adjList[3] = {1, 4, 5};    // D -> B, E, F
    adjList[4] = {3};          // E -> D
    adjList[5] = {1, 3};       // F -> B, D

    std::cout << "\nGraph Adjacency List Representation:\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << vertexNames[i] << " -> ";
        for (int neighbor : adjList[i]) {
            std::cout << vertexNames[neighbor] << " ";
        }
        std::cout << "\n";
    }
}

void printAdjacencyMatrix() {
    std::cout << "\nGraph Adjacency Matrix Representation:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << values[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void determineNodes() {
    int e = -1, d = -1, b = -1, f = -1, a = -1, c = -1;

    //E
    for (int i = 1; i < rows; i++) {
        int connections = 0;
        for (int j = 1; j < cols; j++) {
            if (values[i][j] != "0") connections++;
        }
        if (connections == 1) { e = i; break; }
    }

    //D
    for (int j = 1; j < cols; j++) {
        if (values[e][j] != "0") { d = j; break; }
    }

    //B
    for (int i = 1; i < rows; i++) {
        int connections = 0;
        for (int j = 1; j < cols; j++) {
            if (values[i][j] != "0") connections++;
        }
        if (connections == 4) { b = i; break; }
    }

    //F
    for (int j = 1; j < cols; j++) {
        if (values[d][j] != "0" && j != e && j != b) { f = j; break; }
    }

    //A
    for (int i = 1; i < rows; i++) {
        int connections = 0;
        for (int j = 1; j < cols; j++) {
            if (values[i][j] != "0") connections++;
        }
        if (connections == 2) { a = i; break; }
    }

    //C
    for (int i = 1; i < rows; i++) {
        if (i != e && i != d && i != b && i != f && i != a) { c = i; break; }
    }

    std::cout << "\nA = " << values[a][0] << "\n";
    std::cout << "B = " << values[b][0] << "\n";
    std::cout << "C = " << values[c][0] << "\n";
    std::cout << "D = " << values[d][0] << "\n";
    std::cout << "E = " << values[e][0] << "\n";
    std::cout << "F = " << values[f][0] << "\n";

    std::string distance = values[b][c];
    std::cout << "\nDistance between B and C: " << distance << "\n";
}

int main() {
    printAdjacencyList();
    printAdjacencyMatrix();
    determineNodes();
    return 0;
}
