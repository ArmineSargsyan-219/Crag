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

    int height(Node* node) const {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(Node* node) const {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

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

        return x; // New root after rotation
    }

    // Insert a key and balance the tree
    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            std::cout << "Inserting " << key << " as a new node.\n";
            return new Node(key);
        }

        // Perform standard BST insert
        if (key < node->key) {
            std::cout << "Inserting " << key << " to the left of " << node->key << "\n";
            node->left = insert(node->left, key);
        } else {
            std::cout << "Inserting " << key << " to the right of " << node->key << "\n";
            node->right = insert(node->right, key);
        }

        // Update the height of the current node
        node->height = 1 + std::max(height(node->left), height(node->right));

        // Get the balance factor
        int balance = getBalance(node);
        std::cout << "Balance factor of " << node->key << " is " << balance << "\n";

        // Left Left Case (LL imbalance)
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        return node;
    }

    // Pre-order traversal (root-left-right)
    void preOrder(Node* node) const {
        if (node != nullptr) {
            std::cout << node->key << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // Helper function to delete nodes recursively
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    // Public insert function
    void insert(int key) {
        std::cout << "Inserting " << key << "...\n";
        root = insert(root, key);
    }

    // Display tree in pre-order
    void display() const {
        std::cout << "Pre-order traversal: ";
        preOrder(root);
        std::cout << "\n";
    }
};

// Main function
int main() {
    AVLTree tree;

    // Inserting keys 50, 40, 30 into the AVL tree
    tree.insert(50);
    tree.insert(40);
    tree.insert(30);

    // Display the tree using pre-order traversal
    tree.display();

    return 0;
}
