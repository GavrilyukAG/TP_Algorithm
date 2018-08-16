/*
Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
*/
#include <iostream>
#include <cassert>
#include <stack>
#include <queue>

template <class Node>
int MaxWidth(Node* root) {
    if(root == NULL) {
        return 0;
    }

    std::queue<Node*> Queue;
    Queue.push(root);
    int res = 0;
    int curCount = 0;
    Node* BufNode = NULL;

    while(!Queue.empty()) {
        curCount = Queue.size();
        res = (curCount > res ? curCount : res);

        for(int i = 0; i < curCount; ++i) {
            BufNode = Queue.front();
            Queue.pop();
            if(BufNode->left != NULL) {
                Queue.push(BufNode->left);
            }
            if(BufNode->right != NULL) {
                Queue.push(BufNode->right);
            }
        }
    }
    return res;
}

class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void Insert(int key);
    int GetMaxWidth();

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

    static void delete_node(Node*& root);

    template <class T>
    void postOrderTraversal(T func);
};

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

int BinaryTree::GetMaxWidth() {
    return MaxWidth(root);
}


class Treap {
public:
    Treap();
    ~Treap();

    void Insert(int key, int priority);
    int GetMaxWidth();

private:
    struct Node {
        int key;
        int priority;
        Node* left;
        Node* right;

        Node(int _key = 0, int _priority = 0):
            key(_key),
            priority(_priority),
            left(nullptr),
            right(nullptr)
            {}
    };
    Node* root;

    void Split(Node* node, int key, Node*& left, Node*& right);
    static void delete_node(Node*& root);

    template <class T>
    void postOrderTraversal(T func);
};

Treap::Treap(): root(NULL) {}

Treap::~Treap() {
    postOrderTraversal(delete_node);
}

void Treap::Split(Node* node, int key, Node*& left, Node*& right) {
    if(node == NULL) {
        left = NULL;
        right = NULL;
    } else if(node->key <= key) {
        Split(node->right, key, node->right, right);
        left = node;
    } else {
        Split(node->left, key, left, node->left);
        right = node;
    }
}

void Treap::Insert(int key, int priority) {
    if(root == NULL) {
        root = new Node(key, priority);
        return;
    }

    Node* newRoot = new Node(key, priority);
    Node* parent = root;
    Node* node = root;
    while(1) {
        if(root->priority < priority) {
            Split(root, key, newRoot->left, newRoot->right);
            if(parent->left == root) {
                parent->left = newRoot;
            } else if(parent->right == root) {
                parent->right = newRoot;
            } else {
                root = newRoot;
            }
            break;
        } else if(root->key <= key) {
            if(root->right) {
                parent = root;
                root = root->right;
            } else {
                root->right = newRoot;
                break;
            }
        } else if(root->key > key) {
            if(root->left) {
                parent = root;
                root = root->left;
            } else {
                root->left = newRoot;
                break;
            }
        }
    }

    if(node->priority > root->priority) {
        root = node;
    }
}

int Treap::GetMaxWidth() {
    return MaxWidth(root);
}

template <class T>
void Treap::postOrderTraversal(T func) {
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

void Treap::delete_node(Node*& root) {
    delete root;
    root = NULL;
}

int main() {
    int n = 0;
    int key = 0;
    int priority = 0;
    std::cin >> n;
    assert(n > 0);

    BinaryTree BST;
    Treap Kurevo;

    for(int i = 0; i < n; ++i) {
        std::cin >> key >> priority;
        Kurevo.Insert(key, priority);
        BST.Insert(key);
    }

    std::cout << Kurevo.GetMaxWidth() - BST.GetMaxWidth();

    return 0;
}
