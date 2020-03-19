#include "SplayTree.h"
#include "Tree.h"

#include <iostream>
#include<algorithm>


template<typename T>
void SplayTree<T>::insert(const T &key) {
    if (!Tree<T>::root) {
        Tree<T>::root = std::make_shared<SplayNode>(key);
        return;
    }
    auto temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root);
    while (true) {
        if (temp->data > key) {
            if (!temp->left) {
                temp->left = std::make_shared<SplayNode>(key);

                temp->left->parent = temp;

                temp = temp->left;
                break;
            }
            temp = temp->left;
        }
        else if (temp->data < key) {
            if (!temp->right) {
                temp->right = std::make_shared<SplayNode>(key);

                temp->right->parent = temp;

                temp = temp->right;
                break;
            }
            temp = temp->right;
        }
        else return;
    }
    Tree<T>::root = splay(temp);
}



template<typename T>
void SplayTree<T>::remove(const T &key) noexcept{

}



template<typename T>
SplayIterator<T> SplayTree<T>::find(const T &key) const noexcept{

    if (std::dynamic_pointer_cast<SplayNode>(Tree<T>::root)->data == key){
        return SplayIterator<T>(std::dynamic_pointer_cast<SplayNode>(Tree<T>::root), std::make_shared<ForwardIteration<T>>());
    }


    std::shared_ptr<SplayNode> temp = nullptr;

    if (std::dynamic_pointer_cast<SplayNode>(Tree<T>::root)->data > key){
        temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root)->left;
    } else {
        temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root)->right;
    }


    while (temp != nullptr){
        if (temp->data == key){
            return SplayIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
        } else if (temp->data > key){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    return SplayIterator<T>(nullptr, std::shared_ptr<ForwardIteration<T>>());
}



template<typename T>
void SplayTree<T>::print() const noexcept {
    auto temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root);
    while(temp->previous() != nullptr){
        temp = std::dynamic_pointer_cast<SplayNode>(temp->previous());
    }

    while(temp != nullptr){
        std::cout << temp->data << " ";

        temp = std::dynamic_pointer_cast<SplayNode>(temp->next());
    }
}



template<typename T>
SplayTree<T>::SplayTree() : Tree<T>(){
}

template<typename T>
SplayIterator<T> SplayTree<T>::begin() const noexcept {
    auto temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root);

    while (temp->previous() != nullptr){
        temp = std::dynamic_pointer_cast<SplayNode>(temp->previous());
    }

    return SplayIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
SplayIterator<T> SplayTree<T>::end() const noexcept {
    return SplayIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
SplayIterator<T> SplayTree<T>::rbegin() const noexcept {
    auto temp = std::dynamic_pointer_cast<SplayNode>(Tree<T>::root);

    while(temp->next() != nullptr){
        temp = std::dynamic_pointer_cast<SplayNode>(temp->next());
    }

    return SplayIterator<T>(temp, std::make_shared<ReverseIteration<T>>());
}

template<typename T>
SplayIterator<T> SplayTree<T>::rend() const noexcept {
    return SplayIterator<T>(nullptr, std::make_shared<ReverseIteration<T>>());
}

template<typename T>
void SplayTree<T>::zig(std::shared_ptr<SplayNode> node) noexcept {
    auto& parent = node->parent;
    if (node->isLeftSon()) {
        swap_value(parent->left, node->right, parent);
        swap_value(node->right, parent, node);
    }
    else if (node->isRightSon()) {
        swap_value(parent->right, node->left, parent);
        swap_value(node->left, parent, node);
    }
    parent = nullptr;
}

template<typename T>
void SplayTree<T>::zigzig(std::shared_ptr<SplayNode> node) noexcept {
    auto mostParent = node->parent->parent->parent;
    auto grandparent = node->parent->parent;
    if (grandparent->isLeftSon()) {
        mostParent->left = node;
    }
    else if (grandparent->isRightSon()){
        mostParent->right = node;
    }
    auto parent = node->parent;

    if (node->isLeftSon() && parent->isLeftSon()) {
        swap_value(grandparent->left, parent->right, grandparent);
        swap_value(parent->right, grandparent, parent);
        swap_value(parent->left, node->right, parent);
        swap_value(node->right, parent, node);
    }

    else if (node->isRightSon() && parent->isRightSon()) {
        swap_value(grandparent->right, parent->left, grandparent);
        swap_value(parent->left, grandparent, parent);
        swap_value(parent->right, node->left, parent);
        swap_value(node->left, parent, node);
    }
    node->parent = mostParent;
}

template<typename T>
void SplayTree<T>::zigzag(std::shared_ptr<SplayNode> node) noexcept {
    auto mostParent = node->parent->parent->parent;
    auto grandparent = node->parent->parent;
    if (grandparent->isLeftSon()) {
        mostParent->left = node;
    }
    else if (grandparent->isRightSon()){
        mostParent->right = node;
    }
    auto parent = node->parent;

    if (node->isRightSon() && parent->isLeftSon()) {
        swap_value(grandparent->left, node->right, grandparent);
        swap_value(parent->right, node->left, parent);

        swap_value(node->left, parent, node);
        swap_value(node->right, grandparent, node);
    }
    else if (node->isLeftSon() && parent->isRightSon()){
        swap_value(grandparent->right, node->left, grandparent);
        swap_value(parent->left, node->right, parent);

        swap_value(node->right, parent, node);
        swap_value(node->left, grandparent, node);
    }
    node->parent = mostParent;
}

template<typename T>
std::shared_ptr<typename SplayTree<T>::SplayNode> SplayTree<T>::splay(std::shared_ptr<SplayNode> node) noexcept {
    while (node->parent) {
        if ((node->isRightSon() && node->parent->isLeftSon()) ||
            (node->isLeftSon() && node->parent->isRightSon())) {
            zigzag(node);
        }
        else if ((node->isLeftSon() && node->parent->isLeftSon()) ||
                 (node->isRightSon() && node->parent->isRightSon())) {
            zigzig(node);
        }
        else {
            zig(node);
            return node;
        }
    }
    return node;
}

template<typename T>
std::shared_ptr<typename SplayTree<T>::SplayNode>
SplayTree<T>::merge(std::shared_ptr<SplayNode> lhs, std::shared_ptr<SplayNode> rhs) noexcept {
    if (!lhs) {
        return rhs;
    }
    if (!rhs) {
        return lhs;
    }

    auto max = lhs;

    while (max->next() != nullptr){
        max = max->next();
    }

    auto lhs_root = splay(max);

    lhs_root->right = rhs;
    lhs_root->right->parent = lhs_root;

    return lhs_root;
}

template<typename T>
std::pair<std::shared_ptr<typename SplayTree<T>::SplayNode>, std::shared_ptr<typename SplayTree<T>::SplayNode>>
SplayTree<T>::split(std::shared_ptr<SplayNode> node, const T &key) noexcept {

    auto min = node;
    while (min->previous() != nullptr){
        min = min->previous();
    }

    auto begin = SplayIterator(min, std::make_shared<ForwardIteration<T>>());
    auto end = SplayIterator(nullptr, std::make_shared<ForwardIteration<T>>());

    T upper_bound = std::upper_bound(begin, end, key);


    auto upper_bound_node = node;

    while(upper_bound_node->data != key){
        if (upper_bound_node->data > key){
            upper_bound_node = upper_bound_node->left;
        } else {
            upper_bound_node = upper_bound_node->right;
        }
    }

    auto new_tree = splay(upper_bound_node);
    auto leftTree = new_tree->left;
    leftTree->parent = nullptr;
    new_tree->left = nullptr;
    return std::pair(leftTree, new_tree);
}

template<typename T>
void SplayTree<T>::swap_value(std::shared_ptr<SplayNode> &var, std::shared_ptr<SplayNode> &value,
                             std::shared_ptr<SplayNode> &new_parent) {
    var = value;
    if (var) {
        var->parent = new_parent;
    }
}


template<typename T>
SplayTree<T>::SplayNode::SplayNode(const T &key) : data(key), parent(nullptr), left(nullptr), right(nullptr) {
}




template<typename T>
std::shared_ptr<typename Tree<T>::Node> SplayTree<T>::SplayNode::next() const noexcept {
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
std::shared_ptr<typename Tree<T>::Node> SplayTree<T>::SplayNode::previous() const noexcept {
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

    return parent->left->data == this->data;
}



template<typename T>
bool SplayTree<T>::SplayNode::isRightSon() const noexcept {
    if (!parent){
        return false;
    }

    if (!parent->right){
        return false;
    }

    return parent->right->data == this->data;
}
