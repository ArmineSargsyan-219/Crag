#include <iostream>
#include <algorithm>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;
    int size;  // Size of the subtree rooted at this node

    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr), size(1) {}
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node* &x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;

        // Update size
        x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);
        y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);
    }

    void rotateRight(Node* &x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;

        y->right = x;
        x->parent = y;

        // Update size
        x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);
        y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);
    }

    void fixInsert(Node* &pt) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (pt != root && pt->color == RED && pt->parent->color == RED) {
            parent = pt->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandparent;
                } else {
                    if (pt == parent->right) {
                        rotateLeft(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            } else {
                Node* uncle = grandparent->left;
                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandparent;
                } else {
                    if (pt == parent->left) {
                        rotateRight(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
        }
        root->color = BLACK;
    }

    Node* BSTInsert(Node* root, Node* pt) {
        if (!root) return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        // Update size of the current node
        root->size = 1 + (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0);
        return root;
    }

    Node* search(Node* node, int key) {
        if (!node || key == node->data) return node;
        if (key < node->data) return search(node->left, key);
        else return search(node->right, key);
    }

public:
    RBTree() : root(nullptr) {}

    void insert(int data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixInsert(pt);
    }

    // Search for a node with value k
    Node* searchValue(int k) {
        return search(root, k);
    }
};

// -------------------- Main ---------------------

int main() {
    RBTree tree;

    // Insert values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);

    // Input value of k to search
    int k;
    cout << "Enter a value to search: ";
    cin >> k;

    Node* result = tree.searchValue(k);
    if (result) {
        cout << "Value " << k << " found in the tree!" << endl;
    } else {
        cout << "Value " << k << " not found in the tree." << endl;
    }

    return 0;
}
