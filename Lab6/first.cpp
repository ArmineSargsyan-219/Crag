#include <iostream>
#include <algorithm>
using namespace std;

// Enum for node color
enum Color { RED, BLACK };

// Node structure
struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Class for Red-Black Tree
class RBTree {
private:
    Node* root;

    // Left rotate
    void rotateLeft(Node* &root, Node* &x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Right rotate
    void rotateRight(Node* &root, Node* &x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    // Fix violations after insertion
    void fixInsert(Node* &root, Node* &pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            // Case A: Parent is left child
            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                // Case 1: Uncle is red -> Recoloring
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    // Case 2: pt is right child -> Left rotation
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Case 3: pt is left child -> Right rotation
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            // Case B: Parent is right child
            else {
                Node* uncle_pt = grand_parent_pt->left;

                // Case 1: Uncle is red -> Recoloring
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else {
                    // Case 2: pt is left child -> Right rotation
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Case 3: pt is right child -> Left rotation
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    // Inorder traversal
    void inorderHelper(Node* root) {
        if (root == nullptr) return;
        inorderHelper(root->left);
        cout << root->data << (root->color == RED ? " (R) " : " (B) ");
        inorderHelper(root->right);
    }

    // Recursive height calculation
    int getHeightHelper(Node* node) {
        if (node == nullptr)
            return -1; // height of empty tree
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
    }

    // Recursive black-height calculation
    int getBlackHeightHelper(Node* node) {
        int blackHeight = 0;
        while (node != nullptr) {
            if (node->color == BLACK)
                blackHeight++;
            node = node->left;
        }
        return blackHeight;
    }

public:
    RBTree(): root(nullptr) {}

    void insert(const int &data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixInsert(root, pt);
    }

    // Standard BST insert
    Node* BSTInsert(Node* root, Node* pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    int getHeight() {
        return getHeightHelper(root);
    }

    int getBlackHeight() {
        return getBlackHeightHelper(root);
    }
};

// Main function
int main() {
    RBTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    cout << "Inorder Traversal of Created Tree:\n";
    tree.inorder();

    cout << "\nHeight of Red-Black Tree: " << tree.getHeight() << endl;
    cout << "Black-Height of Red-Black Tree: " << tree.getBlackHeight() << endl;

    return 0;
}
