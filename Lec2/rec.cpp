#include <iostream>
#include <vector>


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> levels;
        traverse(root, 0, levels);
        return levels;
    }

private:
    void traverse(TreeNode* node, int depth, std::vector<std::vector<int>>& levels) {
        if (!node) return;

        if (levels.size() <= depth) levels.push_back({});

        levels[depth].push_back(node->val);

        traverse(node->left, depth + 1, levels);
        traverse(node->right, depth + 1, levels);
    }
};

void printLevelOrder(const std::vector<std::vector<int>>& levels) {
    for (const auto& level : levels) {
        for (int val : level) std::cout << val << " ";
        std::cout << std::endl;
    }
}

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    root->left->left = new TreeNode(10);
    root->left->right = new TreeNode(5);
    

    Solution solution;
    std::vector<std::vector<int>> result = solution.levelOrder(root);
    printLevelOrder(result);

    return 0;
}
