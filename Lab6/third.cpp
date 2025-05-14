#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data): data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root;

    void rotateLeft(Node* &root, Node* &x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
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

    void rotateRight(Node* &root, Node* &x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
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

    void fixInsert(Node* &root, Node* &pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node* uncle_pt = grand_parent_pt->left;

                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

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

    void inorderHelper(Node* root) {
        if (root == nullptr) return;
        inorderHelper(root->left);
        cout << root->data << (root->color == RED ? " (R) " : " (B) ");
        inorderHelper(root->right);
    }

    int getHeightHelper(Node* node) {
        if (node == nullptr)
            return -1;
        return 1 + max(getHeightHelper(node->left), getHeightHelper(node->right));
    }

    int getBlackHeightHelper(Node* node) {
        int blackHeight = 0;
        while (node != nullptr) {
            if (node->color == BLACK)
                blackHeight++;
            node = node->left;
        }
        return blackHeight;
    }

    bool validateRBT(Node* node, int blackCount, int& pathBlackHeight) {
        if (node == nullptr) {
            if (pathBlackHeight == -1) {
                pathBlackHeight = blackCount;
            } else {
                if (blackCount != pathBlackHeight) {
                    cout << "Violation: Black-height mismatch.\n";
                    return false;
                }
            }
            return true;
        }

        if (node->color == RED) {
            if ((node->left && node->left->color == RED) ||
                (node->right && node->right->color == RED)) {
                cout << "Violation: Red node has red child at node " << node->data << "\n";
                return false;
            }
        }

        if (node->color == BLACK)
            blackCount++;

        return validateRBT(node->left, blackCount, pathBlackHeight) &&
               validateRBT(node->right, blackCount, pathBlackHeight);
    }

    int countInRangeHelper(Node* node, int lower, int upper) {
        if (node == nullptr) return 0;

        if (node->data < lower)
            return countInRangeHelper(node->right, lower, upper);
        else if (node->data > upper)
            return countInRangeHelper(node->left, lower, upper);
        else
            return 1 + countInRangeHelper(node->left, lower, upper) +
                       countInRangeHelper(node->right, lower, upper);
    }

public:
    RBTree(): root(nullptr) {}

    void insert(const int &data) {
        Node* pt = new Node(data);
        root = BSTInsert(root, pt);
        fixInsert(root, pt);
    }

    void insertValues(const vector<int>& values) {
        for (int val : values) {
            insert(val);
        }
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

    bool isRedBlackTree() {
        if (root == nullptr) return true;

        if (root->color != BLACK) {
            cout << "Violation: Root is not black.\n";
            return false;
        }

        int blackHeight = -1;
        return validateRBT(root, 0, blackHeight);
    }

    int countInRange(int lower, int upper) {
        return countInRangeHelper(root, lower, upper);
    }
};

int main() {
    RBTree tree;

    vector<int> values = {10, 20, 30, 15, 25, 5, 1};
    tree.insertValues(values);

    cout << "Inorder Traversal of Created Tree:\n";
    tree.inorder();

    cout << "\nHeight of Red-Black Tree: " << tree.getHeight() << endl;
    cout << "Black-Height of Red-Black Tree: " << tree.getBlackHeight() << endl;

    if (tree.isRedBlackTree()) {
        cout << "\nThis is a valid Red-Black Tree.\n";
    } else {
        cout << "\nThis is NOT a valid Red-Black Tree.\n";
    }

    cout << "\nCount in range [10, 25]: " << tree.countInRange(10, 25) << endl;
    cout << "Count in range [1, 5]: " << tree.countInRange(1, 5) << endl;
    cout << "Count in range [0, 100]: " << tree.countInRange(0, 100) << endl;

    return 0;
}
