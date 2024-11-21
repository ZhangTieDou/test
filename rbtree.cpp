//#include <iostream>
//using namespace std;
//
///*
//这段代码中，我们定义了一个 Node 类来表示红黑树中的节点，并定义了一个 RedBlackTree 类来表示红黑树。在 RedBlackTree 中，我们定义了三个函数，分别是 rotateLeft、rotateRight 和 fixViolation。其中，rotateLeft 和 rotateRight 函数用于进行左旋和右旋操作，fixViolation 函数用于修正红黑树中可能出现的违反红黑树性质的情况。
//
//在 main 函数中，我们创建了一个红黑树对象 tree，并插入了一些数据。最后，我们调用 inorder 函数来输出红黑树中的数据。
//*/
//
//enum Color { RED, BLACK };
//
//class Node {
//public:
//    int data;
//    Color color;
//    Node* left, * right, * parent;
//    Node(int data) : data(data) {
//        left = right = parent = NULL;
//        color = RED;
//    }
//};
//
//class RedBlackTree {
//private:
//    Node* root;
//protected:
//    void rotateLeft(Node*&, Node*&);
//    void rotateRight(Node*&, Node*&);
//    void fixViolation(Node*&, Node*&);
//public:
//    RedBlackTree() { root = NULL; }
//    void insert(const int& n);
//    void inorder();
//};
//
//void inorderHelper(Node* root) {
//    if (root == NULL) {
//        return;
//    }
//    inorderHelper(root->left);
//    cout << root->data << " ";
//    inorderHelper(root->right);
//}
//
//void RedBlackTree::inorder() {
//    inorderHelper(root);
//}
//
//void RedBlackTree::rotateLeft(Node*& root, Node*& pt) {
//    Node* pt_right = pt->right;
//    pt->right = pt_right->left;
//    if (pt->right != NULL) {
//        pt->right->parent = pt;
//    }
//    pt_right->parent = pt->parent;
//    if (pt->parent == NULL) {
//        root = pt_right;
//    }
//    else if (pt == pt->parent->left) {
//        pt->parent->left = pt_right;
//    }
//    else {
//        pt->parent->right = pt_right;
//    }
//    pt_right->left = pt;
//    pt->parent = pt_right;
//}
//
//void RedBlackTree::rotateRight(Node*& root, Node*& pt) {
//    Node* pt_left = pt->left;
//    pt->left = pt_left->right;
//    if (pt->left != NULL) {
//        pt->left->parent = pt;
//    }
//    pt_left->parent = pt->parent;
//    if (pt->parent == NULL) {
//        root = pt_left;
//    }
//    else if (pt == pt->parent->left) {
//        pt->parent->left = pt_left;
//    }
//    else {
//        pt->parent->right = pt_left;
//    }
//    pt_left->right = pt;
//    pt->parent = pt_left;
//}
//
//void RedBlackTree::fixViolation(Node*& root, Node*& pt) {
//    Node* parent_pt = NULL;
//    Node* grand_parent_pt = NULL;
//    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
//        parent_pt = pt->parent;
//        grand_parent_pt = pt->parent->parent;
//        if (parent_pt == grand_parent_pt->left) {
//            Node* uncle_pt = grand_parent_pt->right;
//            if (uncle_pt != NULL && uncle_pt->color == RED) {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            }
//            else {
//                if (pt == parent_pt->right) {
//                    rotateLeft(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//                rotateRight(root, grand_parent_pt);
//                swap(parent_pt->color, grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        }
//        else {
//            Node* uncle_pt = grand_parent_pt->left;
//            if (uncle_pt != NULL && uncle_pt->color == RED) {
//                grand_parent_pt->color = RED;
//                parent_pt->color = BLACK;
//                uncle_pt->color = BLACK;
//                pt = grand_parent_pt;
//            }
//            else {
//                if (pt == parent_pt->left) {
//                    rotateRight(root, parent_pt);
//                    pt = parent_pt;
//                    parent_pt = pt->parent;
//                }
//                rotateLeft(root, grand_parent_pt);
//                swap(parent_pt->color, grand_parent_pt->color);
//                pt = parent_pt;
//            }
//        }
//    }
//    root->color = BLACK;
//}
//
//void RedBlackTree::insert(const int& data) {
//    Node* pt = new Node(data);
//    root = pt;
//    fixViolation(root, pt);
//}
//
//int main() {
//    RedBlackTree tree;
//    tree.insert(7);
//    tree.insert(3);
//    tree.insert(18);
//    tree.insert(10);
//    tree.insert(22);
//    tree.insert(8);
//    tree.insert(11);
//    tree.insert(26);
//    tree.inorder();
//    return 0;
//}
