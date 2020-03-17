#include "BTree.h"
#include "Tree.h"

template<typename T>
BTree<T>::BTree() : Tree<T>::root(nullptr) {
}

template<typename T>
BTree<T>::~BTree() {
    delete Tree<T>::root;
}

