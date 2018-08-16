/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
2_3. Выведите элементы в порядке post-order (снизу вверх).
*/
#include <iostream>
#include <cassert>
#include <stack>

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void Insert(int key);
    void PrintTree();

private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int key = 0):
            data(key),
            left(nullptr),
            right(nullptr)
            {}
    };
    Node* root;

    static void print_node(Node*& root);
    static void delete_node(Node*& root);

    template <class T>
    void postOrderTraversal(T func);
};

void BinaryTree::print_node(Node*& root) {
    std::cout << root->data << ' ';
    root = NULL;
}

void BinaryTree::delete_node(Node*& root) {
    delete root;
    root = NULL;
}

BinaryTree::BinaryTree(): root(NULL) {}

BinaryTree::~BinaryTree() {
    postOrderTraversal(delete_node);
}

void BinaryTree::Insert(int key) {
    if(root == NULL) {
        root = new Node(key);
        return;
    }

    Node* parent = root;
    while(1) {
        if(root->data > key) {
            if(!root->left) {
                root->left = new Node(key);
                root = parent;
                return;
            } else {
                root = root->left;
            }
        } else {
            if(!root->right) {
                root->right = new Node(key);
                root = parent;
                return;
            } else {
                root = root->right;
            }
        }
    }
}

void BinaryTree::PrintTree() {
    postOrderTraversal(print_node);
}

template <class T>
void BinaryTree::postOrderTraversal(T func) {
    if(root == NULL) {
        return;
    }
    Node* parent = root;
    std::stack<Node*> treeStack;
    do {
        while(root) {
            if(root->right) {
                treeStack.push(root->right);
            }
            treeStack.push(root);
            root = root->left;
        }

        root = treeStack.top();
        treeStack.pop();

        if(!treeStack.empty() && root->right && treeStack.top() == root->right) {
            treeStack.pop();
            treeStack.push(root);
            root = root->right;
        } else {
            func(root);
        }
    } while(!treeStack.empty());

    root = parent;
}

int main()
{
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    BinaryTree BST;

    for(int i = 0; i < n; ++i) {
        int key = 0;
        std::cin >> key;
        BST.Insert(key);
    }

    BST.PrintTree();

    return 0;
}
