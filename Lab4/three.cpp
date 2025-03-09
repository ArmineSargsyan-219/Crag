#include <iostream>
#include <algorithm>  // For std::max

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Get height of a node
    int height(Node* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    // Get balance factor of a node
    int getBalance(Node* node) const {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    // Right Rotation (For LL Imbalance)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        std::cout << "Performing Right Rotation on node " << y->key << "\n";

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;  // New root after rotation
    }

    // Insert function with balancing
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            std::cout << "Inserting " << key << " as a new node.\n";
            return new Node(key);
        }

        // Standard BST insert
        if (key < node->key) {
            std::cout << "Inserting " << key << " to the left of " << node->key << "\n";
            node->left = insert(node->left, key);
        } else {
            std::cout << "Inserting " << key << " to the right of " << node->key << "\n";
            node->right = insert(node->right, key);
        }

        // Update height
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Get balance factor
        int balance = getBalance(node);
        std::cout << "Balance factor of " << node->key << " is " << balance << "\n";

        // Left Left Case (LL imbalance)
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        return node;
    }

    // Pre-order traversal
    void preOrder(Node* node) const {
        if (node != nullptr) {
            std::cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert function
    void insert(int key) {
        std::cout << "Inserting " << key << "...\n";
        root = insert(root, key);
    }

    // Display the tree in pre-order
    void display() const {
        std::cout << "Pre-order traversal: ";
        preOrder(root);
        std::cout << "\n";
    }
};

int main() {
    AVLTree tree;

    // Insert the given sequence
    tree.insert(100);
    tree.insert(90);
    tree.insert(80);  // LL Rotation at 100
    tree.insert(70);  // LL Rotation at 90
    tree.insert(60);  // LL Rotation at 80

    // Display the tree after balancing
    tree.display();

    return 0;
}
