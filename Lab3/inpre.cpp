#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;  // Adding parent pointer
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

class Solution {
public:
    // Preorder traversal (Root, Left, Right) with parent and depth tracking
    void preorder(TreeNode* node, int depth = 0) {
        if (node == nullptr) return;

        // Print node value with depth and parent information
        cout << "Node: " << node->val 
             << " Depth: " << depth
             << " Parent: " << (node->parent ? to_string(node->parent->val) : "None") << endl;

        // Traverse left and right child
        preorder(node->left, depth + 1);  
        preorder(node->right, depth + 1);
    }

    // Inorder traversal (Left, Root, Right) with parent and depth tracking
    void inorder(TreeNode* node, int depth = 0) {
        if (node == nullptr) return;

        // Traverse left subtree
        inorder(node->left, depth + 1);

        // Print node value with depth and parent information
        cout << "Node: " << node->val 
             << " Depth: " << depth
             << " Parent: " << (node->parent ? to_string(node->parent->val) : "None") << endl;

        // Traverse right subtree
        inorder(node->right, depth + 1);
    }

    // Iterative preorder traversal with depth and parent tracking
    void preorderIterative(TreeNode* root) {
        if (root == nullptr) return;

        stack<pair<TreeNode*, int>> s;  // Pair of node and depth
        s.push({root, 0});

        while (!s.empty()) {
            auto [node, depth] = s.top();
            s.pop();

            // Print node value with depth and parent information
            cout << "Node: " << node->val 
                 << " Depth: " << depth
                 << " Parent: " << (node->parent ? to_string(node->parent->val) : "None") << endl;

            if (node->right) {
                node->right->parent = node;
                s.push({node->right, depth + 1});
            }
            if (node->left) {
                node->left->parent = node;
                s.push({node->left, depth + 1});
            }
        }
    }

    // Iterative inorder traversal with depth and parent tracking
    void inorderIterative(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> s;
        TreeNode* current = root;
        int depth = 0;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
                depth++;
            }

            current = s.top();
            s.pop();

            // Print node value with depth and parent information
            cout << "Node: " << current->val 
                 << " Depth: " << depth
                 << " Parent: " << (current->parent ? to_string(current->parent->val) : "None") << endl;

            current = current->right;
            depth--;
        }
    }
};

int main() {
    // Create a simple binary tree
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    // Set parent pointers
    root->left->parent = root;
    root->right->parent = root;
    root->left->left->parent = root->left;
    root->left->right->parent = root->left;
    root->right->left->parent = root->right;
    root->right->right->parent = root->right;

    Solution solution;

    cout << "Recursive Preorder traversal: " << endl;
    solution.preorder(root);
    cout << endl;

    cout << "Recursive Inorder traversal: " << endl;
    solution.inorder(root);
    cout << endl;

    cout << "Iterative Preorder traversal: " << endl;
    solution.preorderIterative(root);
    cout << endl;

    cout << "Iterative Inorder traversal: " << endl;
    solution.inorderIterative(root);
    cout << endl;

    return 0;
}
