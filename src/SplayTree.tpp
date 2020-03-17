#include "SplayTree.h"
#include "Tree.h"

#include <iostream>

template<typename T>
SplayTree<T>::~SplayTree() {
    delete Tree<T>::root;
}

template<typename T>
void SplayTree<T>::insert(const T &key) {
    if (!Tree<T>::root){
        Tree<T>::root = new SplayTree<T>::SplayNode(key);
    }
    std::cout << Tree<T>::root->data << std::endl;
}

template<typename T>
void SplayTree<T>::remove(const T &key) noexcept{

}

template<typename T>
bool SplayTree<T>::find(const T &key) const noexcept{
    return false;
}

template<typename T>
void SplayTree<T>::print() const noexcept {

}


template<typename T>
SplayTree<T>::SplayNode::SplayNode(const T &key) : Tree<T>::Node(key) {
}



template<typename T>
SplayTree<T>::SplayNode::~SplayNode() {
    delete Tree<T>::root;
}



template<typename T>
typename Tree<T>::Node* SplayTree<T>::SplayNode::next() const noexcept {
    if (right) {
        auto temp = right;
        while (temp->left) {
            temp = temp->left;
        }
        return temp;
    }

    if (!parent){
        return nullptr;
    }

    auto temp = parent;

    while (true) {
        if (!temp->parent) {
            return nullptr;
        }
        if (isLeftSon()) {
            return parent;
        }
        temp = temp->parent;
    }
}



template<typename T>
typename Tree<T>::Node *SplayTree<T>::SplayNode::previous() const noexcept {
    if (left) {
        auto temp = left;
        while (temp->right) {
            temp = temp->right;
        }
        return temp;
    }

    if (!parent){
        return nullptr;
    }

    auto temp = parent;

    while (true) {
        if (!temp->parent) {
            return nullptr;
        }
        if (isRightSon()) {
            return parent;
        }
        temp = temp->parent;
    }
}



template<typename T>
bool SplayTree<T>::SplayNode::isLeftSon() const noexcept {
    if (!parent){
        return false;
    }

    if (!parent->left){
        return false;
    }

    return parent->left == this;
}



template<typename T>
bool SplayTree<T>::SplayNode::isRightSon() const noexcept {
    if (!parent){
        return false;
    }

    if (!parent->right){
        return false;
    }

    return parent->right == this;
}
