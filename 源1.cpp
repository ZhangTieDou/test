// Here is an implementation of a Red-Black Tree in C++:

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    bool color;
    Node* left, * right, * parent;

    Node(int data) {
        this->data = data;
        left = right = parent = NULL;
        this->color = RED;
    }
};

class RBTree {
private:
    Node* root;

protected:
    void rotateLeft(Node*&, Node*&);
    void rotateRight(Node*&, Node*&);
    void fixViolation(Node*&, Node*&);

public:
    RBTree() { root = NULL; }
    void insert(const int& n);
    void inorder();
    void levelOrder();
};

// A function to perform inorder traversal
void inorderHelper(Node* root) {
    if (root == NULL)
        return;

    inorderHelper(root->left);
    cout << root->data << "  ";
    inorderHelper(root->right);
}

/*
 * Returns the height of the tree.
 * The height of an empty tree is -1 and the height of a tree with only one node is 0.
 */
int height(Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

// Function to print level order traversal a tree
void printGivenLevel(Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 0)
        cout << root->data << " ";
    else if (level > 0) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

void levelOrderHelper(Node* root) {
    int h = height(root);
    for (int i = 0; i <= h; i++)
        printGivenLevel(root, i);
}

/*
 * Insert Element into the tree
 */
void RBTree::insert(const int& data) {
    Node* newNode = new Node(data);
    root = newNode;

    // fix the Red-Black Tree properties
    fixViolation(root, newNode);
}

// Function to print inorder traversal of the tree
void RBTree::inorder() {
    inorderHelper(root);
}

// Function to print level order traversal of the tree
void RBTree::levelOrder() {
    levelOrderHelper(root);
}

// Driver Code
int main() {
    RBTree tree;

    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    cout << "Inorder traversal of the constructed Red-Black Tree is: ";
    tree.inorder();

    cout << "\n\nLevel Order traversal of the constructed Red-Black Tree is: ";
    tree.levelOrder();

    return 0;
}

// Function to perform left rotation
void RBTree::rotateLeft(Node*& root, Node*& pt) {
    Node* pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

// Function to perform right rotation
void RBTree::rotateRight(Node*& root, Node*& pt) {
    Node* pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == NULL)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// Function to fix violation of Red-Black Tree properties
void RBTree::fixViolation(Node*& root, Node*& pt) {
    Node* parent_pt = NULL;
    Node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /* Case A:
           Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left) {
            Node* uncle_pt = grand_parent_pt->right;

            /* Case 1:
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                /* Case 2:
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right) {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case 3:
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case B:
           Parent of pt is right child of Grand-parent of pt */
        else {
            Node* uncle_pt = grand_parent_pt->left;

            /* Case 1:
               The uncle of pt is also red
               Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else {
                /* Case 2:
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left) {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case 3:
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}