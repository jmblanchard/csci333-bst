#include "BST.h"
#include <iostream>
#include <assert.h>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {
    assert(root != 0);
    Node<T> *toDelete = root;
    Node<T> *prev = 0;
    bool left = false;

    // find node
    while (toDelete != 0 && toDelete->getValue() != v) {
        prev = toDelete;
        if (toDelete->getValue() < v) {
            toDelete = toDelete->getRightChild();
            left = false;
        }
        else {
            toDelete = toDelete->getLeftChild();
            left = true;
        }
    }

    if (toDelete == 0) // return if not found
        return;

    if (toDelete->getLeftChild() == 0
            && toDelete->getRightChild() == 0) { // no children? 
        if (prev == 0) {
            root = 0;
        } else {
            if (left) {
                prev->setLeftChild(*(toDelete->getRightChild()));
            } else {
                prev->setRightChild(*(toDelete->getRightChild()));
            }
        }

        delete toDelete;
    } else if ((toDelete->getLeftChild() != 0) 
            != (toDelete->getRightChild() != 0)) { // one child?

        if (toDelete->getLeftChild() != 0) { // left child exists
            if (prev == 0) { // toDelete is root
                root = toDelete->getLeftChild();
            } else { // toDelete is not root
                if (left) {
                    prev->setLeftChild(*(toDelete->getLeftChild()));
                } else {
                    prev->setRightChild(*(toDelete->getLeftChild()));
                }
            }
        } else { // right child exists
            if (prev == 0) {
                root = toDelete->getRightChild();
            } else {
                if (left) {
                    prev->setLeftChild(*(toDelete->getRightChild()));
                } else {
                    prev->setRightChild(*(toDelete->getRightChild()));
                }
            }
        }

        delete toDelete;
    } else { // find inorder predecessor (left then right all the way down)
        Node<T> *parent_iop = toDelete;
        Node<T> *iop = toDelete->getLeftChild();

        while (iop->getRightChild() != 0) {
            parent_iop = iop;
            iop = iop->getRightChild();
        }

        iop->setRightChild(*(toDelete->getRightChild()));

        if (parent_iop == toDelete) {
        } else {
            parent_iop->setRightChild(*(iop->getLeftChild()));
        }
        
        if (iop != toDelete->getLeftChild()) {
            iop->setLeftChild(*(toDelete->getLeftChild()));
        }

        if (prev == 0) {
            root = iop;
        } else {
            if (left) {
                prev->setLeftChild(*iop);
            } else {
                prev->setRightChild(*iop);
            }
        }

        delete toDelete;
    }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
