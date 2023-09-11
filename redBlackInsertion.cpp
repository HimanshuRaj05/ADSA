// red black insertion

#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;
};

class RedBlackTree {
private:
    Node* root;

    

    // Left Rotation
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // Right Rotation
    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    // Fix the Red-Black Tree properties after insertion
    void insertFixup(Node* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}


    

    // Insert a value into the Red-Black Tree
    void insert(int data) {
        Node* z = new Node{data, RED, nullptr, nullptr, nullptr};
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }
        insertFixup(z);
    }


     void inOrderPrint(Node* x) {
        if (x != nullptr) {
            inOrderPrint(x->left);
            std::cout << x->data << " (" << (x->color == RED ? "RED" : "BLACK") << ") ";
            inOrderPrint(x->right);
        }
    }

    // Wrapper function to print the entire tree
    void printTree() {
        inOrderPrint(root);
        std::cout << std::endl;
    }
};

int main() {
    RedBlackTree rbTree;
    
    // Insert elements into the Red-Black Tree
    rbTree.insert(10);
    rbTree.insert(20);
    rbTree.insert(30);
    rbTree.insert(15);
    rbTree.insert(5);

    rbTree.printTree();
    
    // Perform any other operations as needed
    return 0;
}
