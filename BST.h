#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "NodeT.h"
#include <stack>
#include <queue>

// Benjamin Valdez Rodriguez

class BST {
    public:
        BST();
        BST(const BST&treeOne);
        ~BST();
        void add(int data);
        bool search(int data);
        void remove(int data);
        void print(int c);
        int height();
        int whatLevelamI(int data);
        void ancestors(int data);
        int count();
        int nearstRelative(int data1, int data2);
        bool operator==(BST const &treeOne);
        void mirror();
        int maxWidth();

    private:
        NodeT *root;
        int howManyChildren(NodeT *r);
        int pred(NodeT *r);
        int succ(NodeT *r);
        void preOrder(NodeT *r);
        void inOrder(NodeT *r);
        void postOrder(NodeT *r);
        void libera(NodeT *r);
        void printLeaves(NodeT *r);
        void printLevelbyLevel();
        int cuenta(NodeT *r);
        int altura(NodeT *r);
        bool compara(NodeT *r, NodeT *r2);
        void changeMirror(NodeT *r);
        NodeT* copyTree(NodeT *r, NodeT *originalTree);
};

BST::BST() {
    root = NULL;
}

NodeT* BST::copyTree(NodeT *r, NodeT *originalTree) {
    if (originalTree == NULL) {
        return NULL;
    }
    else {
        r = new NodeT(originalTree->getData());
        r->setLeft(copyTree(r->getLeft(), originalTree->getLeft()));
        r->setRight(copyTree(r->getRight(), originalTree->getRight()));
        return r;
    }
}
BST::BST(const BST&treeOne) {
    if (treeOne.root == NULL) {
        root = NULL;
    }
    else {
        root = copyTree(this->root, treeOne.root);
    }
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

void BST::printLeaves(NodeT *r) {
    if (r != NULL) {
        if (r->getLeft() == NULL && r->getRight() == NULL) {
            cout << r->getData() << " ";
        }
        else {
            printLeaves(r->getLeft());
            printLeaves(r->getRight());
        }
    }
}

void BST::printLevelbyLevel() {
    queue<NodeT*> fila;
    if (root != NULL) {
        fila.push(root);
        NodeT *curr;
        while (!fila.empty()) {
            curr = fila.front();
            fila.pop();
            cout << curr->getData() << " ";
            if (curr->getLeft() != NULL) {
                fila.push(curr->getLeft());
            }
            if (curr->getRight() != NULL) {
                fila.push(curr->getRight());
            }
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
        case 4:
            printLeaves(root);
            break;
        case 5:
            printLevelbyLevel();
            break;
    }
    cout << endl;
}

int BST::altura(NodeT *r) {
    if (r == NULL) {
        return 0;
    }
    int left = altura(r->getLeft());
    int right = altura(r->getRight());
    return 1 + (left > right ? left : right);
}

int BST::height() {
    return altura(root);
}

int BST::whatLevelamI(int data) {
    NodeT *curr = root;
    int nivel = 0;
    while (curr!= NULL) {
        if (curr->getData() == data) {
            return nivel;
        }
        nivel++;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    return -1;
}

void BST::ancestors(int data) {
    NodeT* curr = root;
    stack<int> pila;
    while (curr != NULL) {
        if (curr->getData() == data) {
            if (pila.empty()) {
                cout << "NO EXISTEN ANCESTROS" << endl;
            }
            else {
                while (!pila.empty()) {
                    cout << pila.top() << " ";
                    pila.pop();
                }
                cout << endl;
            }
            return;
        }
        pila.push(curr->getData());
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    cout << "EL DATO NO EXISTE";
}

int BST::cuenta(NodeT *r) {
    if (r == NULL) {
        return 0;
    }
    return 1 + cuenta(r->getLeft()) + cuenta(r->getRight());
}

int BST::count() {
    return cuenta(root);
}

bool BST::compara(NodeT *r, NodeT *r2) {
    if (r != NULL) {
        if (r->getData() != r2->getData()) {
            return false;
        }
    }
    return true;
}

bool BST::operator==(const BST &treeOne) {
    NodeT *curr = root, *otherCurr = treeOne.root;
    int treeOnesize, treeTwosize;
    queue<NodeT*> myQueueOne;
    queue<NodeT*> myQueueTwo;

    if (curr == NULL && otherCurr == NULL) {
        return true;
    }

    if (root != NULL && otherCurr != NULL) {
        myQueueOne.push(curr);
        myQueueTwo.push(otherCurr);

        while (!myQueueOne.empty() && !myQueueTwo.empty()) {
            treeOnesize = myQueueOne.size();
            treeTwosize = myQueueTwo.size();

            if (treeOnesize != treeTwosize) {
                return false;
            }

            while (treeOnesize > 0 && treeTwosize > 0) {
                curr = myQueueOne.front();
                myQueueOne.pop();

                otherCurr = myQueueTwo.front();
                myQueueTwo.pop();

                if (curr->getData() != otherCurr->getData()) {
                    return false;
                }

                if (curr->getLeft() != NULL) {
                myQueueOne.push(curr->getLeft());
                }
                if (curr->getRight() != NULL) {
                myQueueOne.push(curr->getRight());
                }

                if (otherCurr->getLeft() != NULL) {
                myQueueTwo.push(otherCurr->getLeft());
                }
                if (otherCurr->getRight() != NULL) {
                myQueueTwo.push(otherCurr->getRight());
                }

                treeOnesize--;
                treeTwosize--;
            }

        }
    }
    else {
        return false;
    }

    return true;
}

int BST::nearstRelative(int data1, int data2) {
    NodeT *curr = root, *father = NULL;
    while (curr != NULL) {
        if ((curr->getData() < data1 && curr->getData() > data2) || (curr->getData() > data1 && curr->getData() < data2)) {
            return curr->getData();
        }
        if (curr->getData() != data1 && curr->getData() != data2) {
            father = curr;
        }
        else {
            return father->getData();
        }

        //Preguntar si te dan la root, y si no existe

        if (curr->getData() < data1 && curr->getData() < data2) {
            curr = curr->getRight();
        }
        else if (curr->getData() > data1 && curr->getData() > data2){
            curr = curr->getLeft();
        }
        else {
            break;
        }
    }
    return -1;
}

void BST::mirror() {
    NodeT *curr = root, *temp;
    queue<NodeT*> myQueue;

    if (curr == NULL) {
        return;
    }

    myQueue.push(curr);
    while(!myQueue.empty()) {
        curr = myQueue.front();
        myQueue.pop();

        temp = curr->getLeft();
        curr->setLeft(curr->getRight());
        curr->setRight(temp);

        if (curr->getLeft() != NULL) {
            myQueue.push(curr->getLeft());
        }
        if (curr->getRight() != NULL) {
            myQueue.push(curr->getRight());
        }
    }
}

int BST::maxWidth() {
    int maxNodes = 0, levelNodes = 0;
    queue<NodeT*> fila;
    if (root != NULL) {
        fila.push(root);
        NodeT *curr;
        while (!fila.empty()) {
            levelNodes = fila.size();

            if (levelNodes > maxNodes) {
                maxNodes = levelNodes;
            }

            while (levelNodes > 0) {
                curr = fila.front();
                fila.pop();

                if (curr->getLeft() != NULL) {
                fila.push(curr->getLeft());
                }
                if (curr->getRight() != NULL) {
                fila.push(curr->getRight());
                }
                levelNodes--;
            }

        }
    }
    return maxNodes;
}

//LUNES
//Copy constructor
// Simular el recorrido en preorden sin usar el add
// Usar recursividad

//operador ==
// Recorrido en preorden de los 2 apuntadores, si en un momento son diferentes adios

// Mirror
// Voltearlo, pruebalo y borrarlo al final

// nearstRelative
// Si uno de los dos no existe, pues no, si son como padre e hijo, regresa el abuelo (el ancestro mas cercano)

// maxWidht
// recorrido nivel por nivel y checar cuando hay cambio de nivel

// MIERCOLES
//isBalanced
// Cual es la altura de mi arbol izquierdo, cual es la altura del derecho, si la diferencia es menor de 1, adios

//diamater
// Regresar la longitud maxima (Esta facil si entiendes el de altura) (Regresar un entero con la altura)
// No esperen esto en el examen

//isBalanced
// es parte de lo que vamos a ver el martes
//

#endif // BST_H_INCLUDED
