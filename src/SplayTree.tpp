#include "SplayTree.h"
#include "Tree.h"

#include <iostream>

template<typename T>
SplayTree<T>::~SplayTree() {
    delete Tree<T>::root;
}



template<typename T>
void SplayTree<T>::insert(const T &key) {
    if (Tree<T>::root == nullptr){
        Tree<T>::root = new SplayNode(key);
        return;
    }

    auto temp = dynamic_cast<SplayNode*>(Tree<T>::root);

    while(true){
        if (temp->data < key){
            if (temp->right){
                temp = temp->right;
            } else {
                temp->right = new SplayNode(key);
                temp->right->parent = temp;
                return;
            }
        } else if (temp->data > key){
            if (temp->left){
                temp = temp->left;
            } else {
                temp->left = new SplayNode(key);
                temp->left->parent = temp;
                return;
            }
        } else {
            return;
        }
    }
}



template<typename T>
void SplayTree<T>::remove(const T &key) noexcept{

}



template<typename T>
BaseIterator<T> SplayTree<T>::find(const T &key) const noexcept{

    if (Tree<T>::root->data == key){
        return BaseIterator<T>(Tree<T>::root, std::make_shared<ForwardIteration<T>>());
    }


    SplayNode* temp = nullptr;

    if (Tree<T>::root->data > key){
        temp = dynamic_cast<SplayNode*>(Tree<T>::root)->left;
    } else {
        temp = dynamic_cast<SplayNode*>(Tree<T>::root)->right;
    }


    while (temp != nullptr){
        if (temp->data == key){
            return BaseIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
        } else if (temp->data > key){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    return BaseIterator<T>(nullptr, std::shared_ptr<ForwardIteration<T>>());
}



template<typename T>
void SplayTree<T>::print() const noexcept {
    printNode(dynamic_cast<SplayNode*>(Tree<T>::root));
}



template<typename T>
void SplayTree<T>::printNode(SplayTree::SplayNode* node) noexcept {
    if (!node){
        return;
    }

    printNode(node->left);
    std::cout << node->data << " ";
    printNode(node->right);
}

template<typename T>
SplayTree<T>::SplayTree() : Tree<T>(){
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

    if (isLeftSon()){
        return parent;
    }

    auto temp = parent;

    while (true) {
        if (!temp->parent) {
            return nullptr;
        }
        if (temp->isLeftSon()) {
            return temp->parent;
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

    if (isRightSon()){
        return parent;
    }

    auto temp = parent;

    while (true) {
        if (!temp->parent) {
            return nullptr;
        }
        if (temp->isRightSon()) {
            return temp->parent;
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
