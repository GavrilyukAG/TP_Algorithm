/*
4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).
Формат входных данных.
Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
Формат выходных данных.
На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).
*/
#include <iostream>
#include <cassert>

#include <stack>

class AVLTree {
public:
    AVLTree();

    void Insert(int key);
    void Remove(int key);
    bool Has(int key);

    //------------------
    void postOrderTraversal() {
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
                std::cout << root->key << ' ';
                root = NULL;
            }
        } while(!treeStack.empty());

        root = parent;
    }
    //--------------------------

    int inOrderKStat(int key) {
        if(root == NULL) {
            return 0;
        }

        int KStat = 0;
        Node* parent = root;
        std::stack<Node*> treeStack;
        while(1) {
            if(root) {
                treeStack.push(root);
                root = root->right;
            } else {
                if(!treeStack.empty()) {
                    root = treeStack.top();
                    treeStack.pop();
                    // std::cout << root->key << ' ';
                    if(root->key == key) {
                        root = parent;
                        return KStat;
                    }
                    ++KStat;
                    root = root->left;
                } else {
                    break;
                }
            }
        }

        root = parent;
    }

    int inOrderKey(int value) {
        if(root == NULL) {
            return -1;
        }

        int iter = 0;
        Node* parent = root;
        std::stack<Node*> treeStack;
        while(1) {
            if(root) {
                treeStack.push(root);
                root = root->right;
            } else {
                if(!treeStack.empty()) {
                    root = treeStack.top();
                    treeStack.pop();
                    // std::cout << root->key << ' ';
                    if(iter == value) {
                        root = parent;
                        return root->key;
                    }
                    ++iter;
                    root = root->left;
                } else {
                    break;
                }
            }
        }

        root = parent;
    }


private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int value):
            key(value),
            height(1),
            left(nullptr),
            right(nullptr)
            {}
    };

    Node* root;

    void insert(Node*& root, int key);
    void remove(Node*& root, int key);
    int getHeight(Node* root);
    int balance(Node* root);
    void fixHeight(Node*& root);
    void fixBalance(Node*& root);
    void rotateLeft(Node*& root);
    void rotateRight(Node*& root);

};

AVLTree::AVLTree(): root(NULL) {}

void AVLTree::Insert(int key) {
    insert(root, key);
}

bool AVLTree::Has(int key) {
    Node* buf = root;
    while(root) {
        if(root->key == key) {
            root = buf;
            return true;
        } else if(root->key > key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    root = buf;
    return false;
}

void AVLTree::Remove(int key) {
    remove(root, key);
}

void AVLTree::insert(Node*& root, int key) {
    if(!root) {
        root = new Node(key);
        return;
    }

    if(root->key < key) {
        insert(root->right, key);
    } else {
        insert(root->left, key);
    }
    fixBalance(root);
}

void AVLTree::remove(Node*& root, int key) {
    if(!root) {
        return;
    }

    if(root->key < key) {
        remove(root->right, key);
    } else if(root->key > key) {
        remove(root->left, key);
    } else {
        Node* leftSon = root->left;
        Node* rightSon = root->right;
        // delete root;
        if(!leftSon) {
            root = rightSon;
            return;
        }

        Node* maxNodeParent = leftSon;
        Node* maxNode = leftSon->right;
        while(maxNode->right) {
            maxNodeParent = maxNode;
            maxNode = maxNode->right;
        }

        (maxNodeParent->right == maxNode ? maxNodeParent->right : maxNodeParent->left) = maxNode->left;
        root = maxNode;
        root->left = leftSon;
        root->right = rightSon;
        fixBalance(root);
    }
    fixBalance(root);
}

int AVLTree::getHeight(Node* root) {
    return root ? root->height : 0;
}

int AVLTree::balance(Node* root) {
    return getHeight(root->right) - getHeight(root->left);
}

void AVLTree::fixHeight(Node*& root) {
    assert(root != NULL);
    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

void AVLTree::rotateLeft(Node*& root) {
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root = tmp;

    fixHeight(root);
    fixHeight(root->left);
}

void AVLTree::rotateRight(Node*& root) {
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root = tmp;

    fixHeight(root);
    fixHeight(root->right);
}

void AVLTree::fixBalance(Node*& root) {
    assert(root != NULL);

    if(balance(root) == 2) {
        if(balance(root->right) < 0) {
            rotateRight(root->right);
        }
        rotateLeft(root);
    } else if(balance(root) == -2) {
        if(balance(root->left) < 0) {
            rotateLeft(root->left);
        }
        rotateRight(root);
    } else {
        fixHeight(root);
    }
}


int main() {
    int n = 0;
    std::cin >> n;
    assert(n > 0);

    AVLTree myTree;

    int command = 0;
    int value = 0;
    for(int i = 0; i < n; ++i) {
        std::cin >> command >> value;
        switch(command) {
            case 1:
                myTree.Insert(value);
                // std::cout << myTree.inOrderKStat(value) << std::endl;
                break;
            case 2:
                myTree.Remove(value);
                break;
            default:
                break;
        }
    }
    // myTree.inOrder();
    // std::cout << std::endl;
    // myTree.postOrderTraversal();

    return 0;
}
