#include <iostream>
#include <vector>
#include <climits>

class Graph {
private:
    const int rows = 7, cols = 7;
    int** values;  

public:
    Graph() {
        values = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            values[i] = new int[cols];
        }

        int temp[7][7] = {
            {0, 5, 0, 12, 0, 0, 25},
            {5, 0, 0, 8, 0, 0, 0},
            {0, 0, 0, 2, 4, 5, 10},
            {12, 8, 2, 0, 0, 0, 0},
            {0, 0, 4, 0, 0, 0, 5},
            {0, 0, 0, 0, 0, 0, 5},
            {25, 0, 10, 0, 5, 5, 0}
        };

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                values[i][j] = temp[i][j];
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < rows; ++i) {
            delete[] values[i];
        }
        delete[] values;
    }

    int getDistance(int start, int end) const {
        return values[start][end];
    }

    int calculatePathDistance(const std::vector<int>* path) const {
        int totalDistance = 0;
        for (size_t i = 0; i < path->size() - 1; ++i) {
            totalDistance += getDistance((*path)[i], (*path)[i + 1]);
        }
        return totalDistance;
    }

    void calculateShortestPath() const {
        std::vector<int>* paths[] = {
            new std::vector<int>{0, 3, 2, 4, 6},  
            new std::vector<int>{0, 1, 3, 2, 4, 6},
            new std::vector<int>{0, 6}  
        };

        int shortestDistance = INT_MAX; 
        std::vector<int>* shortestPath = nullptr;  

        for (auto path : paths) {
            int pathDistance = calculatePathDistance(path);
            if (pathDistance < shortestDistance) {
                shortestDistance = pathDistance;
                shortestPath = path;  
            }
        }

        std::cout << "\nShortest Path from A to G: ";
        for (size_t i = 0; i < shortestPath->size(); ++i) {
            std::cout << char('A' + (*shortestPath)[i]); 
            if (i != shortestPath->size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << "\nTotal distance: " << shortestDistance << "\n";

        for (auto path : paths) {
            delete path;
        }
    }
};

int main() {
    Graph graph;
    graph.calculateShortestPath();
    return 0;
}
