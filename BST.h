#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "NodeT.h"
#include <stack>
#include <queue>

// Benjamin Valdez Rodriguez

class BST {
    public:
        BST();
        ~BST();
        void add(int data);
        bool search(int data);
        void remove(int data);
        void print(int c);
        int height();
        int whatLevelamI(int data);
        void ancestors(int data);

    private:
        NodeT *root;
        int howManyChildren(NodeT *r);
        int pred(NodeT *r);
        int succ(NodeT *r);
        void preOrder(NodeT *r);
        void inOrder(NodeT *r);
        void postOrder(NodeT *r);
        void libera(NodeT *r);
        void levelXlevel();
        int calculateHeight(NodeT *r);
};

BST::BST() {
    root = NULL;
}

void BST::libera(NodeT *r) {
    if (r != NULL) {
        libera(r->getLeft());
        libera(r->getRight());
        delete r;
    }
}

BST::~BST() {
    libera(root);
}

bool BST::search(int data) {
    NodeT *curr = root;
    while (curr != NULL) {
        if (curr->getData() == data) {
            return true;
        }
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    return false;
}

void BST::add(int data) {
    NodeT *curr = root;
    NodeT *father = NULL;

    while (curr != NULL) {
        if (curr->getData() == data) {
            return;
        }
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (father == NULL) {
        root = new NodeT(data);
    }
    else {
        if (father->getData() > data) {
            father->setLeft(new NodeT(data));
        }
        else {
            father->setRight(new NodeT(data));
        }
    }
}

int BST::howManyChildren(NodeT *r) {
    int cant = 0;
    if (r ->getLeft() != NULL) {
        cant++;
    }
    if (r ->getRight() != NULL) {
        cant++;
    }
    return cant;
}

int BST::pred(NodeT *r) {
    NodeT *aux = r->getLeft();
    while (aux->getRight() != NULL) {
        aux = aux->getRight();
    }
    return aux->getData();
}

int BST::succ(NodeT *r) {
    NodeT *aux = r->getRight();
    while (aux->getRight() != NULL) {
        aux = aux->getLeft();
    }
    return aux->getData();
}

void BST::remove(int data) {
    NodeT *curr = root;
    NodeT *father = NULL;
    int x;
    //El orden es imporante aqui porque no entra a NULL
    while (curr != NULL && curr->getData() != data) {
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (curr == NULL) {
        return;
    }
    int ch = howManyChildren(curr);
    switch (ch) {
        case 0:
            if (father == NULL) {
                root = NULL;
            }
            else {
                if (father->getData() > data) {
                    father->setLeft(NULL);
                }
                else {
                    father->setRight(NULL);
                }
            }
            delete curr;
            break;
        case 1:
            if (father == NULL) {
                if (curr->getLeft() != NULL) {
                    root = curr->getLeft();
                }
                else {
                    root = curr->getRight();
                }
            }
            else {
                if (father->getData() > data) {
                    if (curr->getLeft() != NULL) {
                        father->setLeft(curr->getLeft());
                    }
                    else {
                        father->setLeft(curr->getRight());
                    }
                }
                else {
                    if (curr->getLeft() != NULL) {
                        father->setRight(curr->getLeft());
                    }
                    else {
                        father->setRight(curr->getRight());
                    }
                }
            }
            delete curr;
            break;
        case 2:
            x = pred(curr);
            remove(x);
            curr->setData(x);
            break;
    }
}

void BST::preOrder(NodeT *r) {
    if (r != NULL) {
        cout << r ->getData() << " ";
        preOrder(r->getLeft());
        preOrder(r->getRight());
    }
}
void BST::inOrder(NodeT *r) {
    if (r != NULL) {
        inOrder(r->getLeft());
        cout << r->getData() << " ";
        inOrder(r->getRight());
    }
}

void BST::postOrder(NodeT *r) {
    if (r  != NULL) {
        postOrder(r->getLeft());
        postOrder(r->getRight());
        cout << r->getData() << " ";
    }
}

void BST::levelXlevel() {
    NodeT *curr = root;
    queue<NodeT*> treepointer;

    if (curr != NULL) {
        treepointer.push(curr);
    }
    while (!treepointer.empty()) {
        curr = treepointer.front();
        treepointer.pop();
        cout << curr->getData() << " ";
        if (curr->getLeft() != NULL) {
            treepointer.push(curr->getLeft());
        }
        if (curr->getRight() != NULL) {
            treepointer.push(curr->getRight());
        }
    }

}

void BST::print(int c) {
// 1 - PreOrder
// 2 - InOrder
// 3 - PostOrder
    switch (c) {
        case 1:
            preOrder(root);
            break;
        case 2:
            inOrder(root);
            break;
        case 3:
            postOrder(root);
            break;
        case 5:
            levelXlevel();
            break;
    }
    cout << endl;
}

int BST::calculateHeight(NodeT *r) {
    int left, right;

    if (r == NULL) {
        return 0;
    }
    left = calculateHeight(r->getLeft());
    right = calculateHeight(r->getRight());

    if (left > right) {
        return left+1;
    }
    else {
        return right+1;
    }

    return 0;
}

int BST::height() {
    if (root == NULL) {
        return 0;
    }
    return calculateHeight(root);
}

int BST::whatLevelamI(int data) {
    NodeT *curr = root;
    int level = 0;

    if (root == NULL) {
        return -1;
    }

    while (curr->getData() != data) {
        if (curr->getData() < data) {
            curr = curr->getRight();
        }
        else {
            curr = curr->getLeft();
        }
        level++;

        if (curr == NULL) {
        return -1;
        }
    }
    return level;
}

void BST::ancestors(int data) {
    NodeT *curr = root;
    stack<int> family;
    bool check = false;

    if (root == NULL) {
        cout << "Esta vacio";
        return;
    }

    while (curr->getData() != data) {
        family.push(curr->getData());
        if (curr->getData() < data) {
            if (curr->getRight() != NULL)
                curr = curr->getRight();
            else {
                check = true;
                break;
            }
        }
        else {
            if (curr->getLeft() != NULL)
                curr = curr->getLeft();
            else {
                check = true;
                break;
            }
        }

    }

    if (check) {
        cout << "No existe el dato";
    }

    if (family.size() == 0) {
        cout << "No tiene ancestros";
    }

    while (!family.empty() && !check) {
        cout << family.top() << " ";
        family.pop();
    }
}

#endif // BST_H_INCLUDED
