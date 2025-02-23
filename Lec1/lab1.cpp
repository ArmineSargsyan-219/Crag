#include <iostream>
#include <vector>
#include <list>

class Graph {
private:
    static const int rows = 7, cols = 7;
    std::string values[rows][cols] = {
        {"0",  "n1", "n2", "n3", "n4", "n5", "n6"},
        {"n1", "0",  "10", "0",  "0",  "8",  "5"},
        {"n2", "10", "0",  "0",  "20", "12", "0"},
        {"n3", "0",  "0",  "0",  "4",  "0",  "0"},
        {"n4", "0",  "20", "4",  "0",  "15", "0"},
        {"n5", "8",  "12", "0",  "15", "0",  "7"},
        {"n6", "5",  "0",  "0",  "0",  "7",  "0"}
    };

    std::vector<char> vertexNames = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<std::list<int>> adjList;

public:
    Graph() {
        adjList.resize(6);
        adjList[0] = {1, 2};       // A -> B, C
        adjList[1] = {0, 2, 3, 5}; // B -> A, C, D, F
        adjList[2] = {0, 1};       // C -> A, B
        adjList[3] = {1, 4, 5};    // D -> B, E, F
        adjList[4] = {3};          // E -> D
        adjList[5] = {1, 3};       // F -> B, D
    }

    void printAdjacencyList() {
        std::cout << "\nGraph Adjacency List Representation:\n";
        for (int i = 0; i < vertexNames.size(); i++) {
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

    void findNodes() {
        int* nodes = new int[6]; 
        int* connections = new int[rows]; 

        for (int i = 0; i < 6; i++) {
            *(nodes + i) = -1;
        }

        for (int i = 0; i < rows; i++) {
            *(connections + i) = 0;
        }

        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                if (values[i][j] != "0") {
                    (*(connections + i))++;  
                }
            }
        }
        

        for (int i = 1; i < rows; i++) {
            if (*(connections + i) == 1) *(nodes + 4) = i; // E
            else if (*(connections + i) == 4) *(nodes + 1) = i; // B
            else if (*(connections + i) == 2) *(nodes + 0) = i; // A
        }

        for (int j = 1; j < cols; j++) {
            if (values[*(nodes + 4)][j] != "0") *(nodes + 3) = j; // D
        }

        for (int j = 1; j < cols; j++) {
            if (values[*(nodes + 3)][j] != "0" && j != *(nodes + 4) && j != *(nodes + 1)) *(nodes + 5) = j; // F
        }

        for (int i = 1; i < rows; i++) {
            if (i != *(nodes + 0) && i != *(nodes + 1) && i != *(nodes + 3) && i != *(nodes + 4) && i != *(nodes + 5)) {
                *(nodes + 2) = i; // C
                break;
            }
        }

        std::cout << "\nA = " << values[*(nodes + 0)][0] << "\n";
        std::cout << "B = " << values[*(nodes + 1)][0] << "\n";
        std::cout << "C = " << values[*(nodes + 2)][0] << "\n";
        std::cout << "D = " << values[*(nodes + 3)][0] << "\n";
        std::cout << "E = " << values[*(nodes + 4)][0] << "\n";
        std::cout << "F = " << values[*(nodes + 5)][0] << "\n";

        std::string distance = values[*(nodes + 1)][*(nodes + 2)];
        std::cout << "\nDistance between B and C: " << distance << "\n";

        delete[] nodes; 
        delete[] connections; 
    }
};

int main() {
    Graph graph;
    graph.printAdjacencyList();
    graph.printAdjacencyMatrix();
    graph.findNodes();
    return 0;
}
