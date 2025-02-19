#include <iostream>
#include <vector>
#include <algorithm> 

const int rows = 8, cols = 8;

int values[8][8] = {
    {0, 5, 0, 12, 0, 0, 0, 25},   
    {5, 0, 0, 8, 0, 0, 0, 0},    
    {0, 0, 0, 2, 4, 5, 10, 0},
    {12, 8, 2, 0, 0, 0, 0, 0},   
    {0, 0, 4, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {25, 0, 10, 0, 5, 5, 0, 0}  
};

int getDistance(int start, int end) {
    return values[start][end];
}

void calculateShortestPath() {
    int A_to_D = getDistance(0, 3); 
    int D_to_C = getDistance(3, 2);  
    int C_to_E = getDistance(2, 4);   
    int E_to_G = getDistance(4, 7);   
    int C_to_G = getDistance(2, 7);   
    int A_to_B = getDistance(0, 1);  
    int B_to_D = getDistance(1, 3);   
    int A_to_G = getDistance(0, 7);   

    int A_to_d = 12;
    int D_to_c = 2;
    int C_to_e = 4;
    int E_to_g = 5;
    int C_to_g = 10;
    int A_to_b = 5;
    int B_to_d = 8;
    int A_to_g = 25;

    int path1 = A_to_d + D_to_c + C_to_e + E_to_g; 

    int path2 = A_to_b + B_to_d + D_to_c + C_to_e + E_to_g;

    int path3 = A_to_g;

    if (path1 <= path2 && path1 <= path3) {
        std::cout << "\nShortest Path from A to G: A -> D -> C -> E -> G\n";
        std::cout << "Total distance: " << path1 << "\n";
    } else if (path2 <= path1 && path2 <= path3) {
        std::cout << "\nShortest Path from A to G: A -> B -> D -> C -> E -> G\n";
        std::cout << "Total distance: " << path2 << "\n";
    } else if (path3 <= path1 && path3 <= path2) {
        std::cout << "\nShortest Path from A to G: A -> G\n";
        std::cout << "Total distance: " << path3 << "\n";
    }
}

int main() {
    calculateShortestPath();
    return 0;
}
