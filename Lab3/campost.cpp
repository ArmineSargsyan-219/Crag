#include <iostream>
#include <stack>
#include <unordered_map>
#include <queue>


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    char camera;  
    TreeNode() : val(0), left(nullptr), right(nullptr), camera('.') {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), camera('.') {}
};

class Solution {
public:
    int minCameraCover(TreeNode* root) {
        if (root == nullptr) return 0;

        std::unordered_map<TreeNode*, int> state;  
        std::stack<TreeNode*> s;

        s.push(root);

        while (!s.empty()) {
            TreeNode* node = s.top();
            if (state.find(node) != state.end()) {
                s.pop();
                int leftState = node->left ? state[node->left] : 1;
                int rightState = node->right ? state[node->right] : 1;

                if (leftState == 0 || rightState == 0) {
                    state[node] = 2;
                    node->camera = 'C';  
                } else if (leftState == 2 || rightState == 2) {
                    state[node] = 1;
                } else {
                    state[node] = 0;
                }
            } else {
                if (node->right) s.push(node->right);
                if (node->left) s.push(node->left);
                state[node] = -1; 
            }
        }

        int cameraCount = 0;
        if (state[root] == 0) {
            cameraCount++;
            root->camera = 'C';  
        }

        for (auto& entry : state) {
            if (entry.second == 2) {
                cameraCount++;
            }
        }

        return cameraCount;
    }

    void printTree(TreeNode* root) {
        if (!root) return;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                std::cout << "Node " << node->val << (node->camera == 'C' ? " (Camera)" : "") << " ";

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    Solution solution;
    int cameras = solution.minCameraCover(root);

    std::cout << "Minimum number of cameras: " << cameras << std::endl;
    
    solution.printTree(root);

    return 0;
}
