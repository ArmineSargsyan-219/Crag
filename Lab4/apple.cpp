#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    int dfs(int node, int parent, std::unordered_map<int, std::vector<int>>& tree, std::vector<bool>& hasApple) {
        int totalTime = 0;
        
        for (int child : tree[node]) {
            if (child == parent) continue; 
            
            int childTime = dfs(child, node, tree, hasApple);
            
            if (childTime > 0 || hasApple[child]) {
                std::cout << "Traversing edge: " << node << " -> " << child << " (cost 2)" << std::endl;
                totalTime += childTime + 2; 
            }
        }

        std::cout << "Returning time for node " << node << ": " << totalTime << std::endl;
        return totalTime;
    }

    void printTree(int node, int parent, std::unordered_map<int, std::vector<int>>& tree, const std::vector<bool>& hasApple) {
        std::cout << "Node " << node << " -> Children: ";
        
        for (int child : tree[node]) {
            if (child != parent) {
                std::cout << child << " ";
            }
        }
        
        if (hasApple[node]) {
            std::cout << "(Apple)";
        } else {
            std::cout << "(No Apple)";
        }
        
        std::cout << std::endl;

        for (int child : tree[node]) {
            if (child != parent) {
                printTree(child, node, tree, hasApple);  // Recursive DFS-like call to print subtrees
            }
        }
    }

    int minTime(int n, std::vector<std::vector<int>>& edges, std::vector<bool>& hasApple) {
        std::unordered_map<int, std::vector<int>> tree;
        
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }

        std::cout << "Tree structure with apples:" << std::endl;
        printTree(0, -1, tree, hasApple);

        return dfs(0, -1, tree, hasApple);
    }
};

int main() {
    Solution sol;
    
    int n = 7;
    std::vector<std::vector<int>> edges = {{0,1},{0,2},{1,4},{1,5},{2,3},{2,6}};
    std::vector<bool> hasApple = {false, false, true, false, true, true, false};
    
    std::cout << "Minimum time to collect all apples: " << sol.minTime(n, edges, hasApple) << " seconds" << std::endl;
    
    return 0;
}
