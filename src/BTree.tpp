#include "BTree.h"
#include "Tree.h"

#include <iostream>


template<typename T>
void BTree<T>::insert(const T &key) {

}



template<typename T>
void BTree<T>::remove(const T &key) noexcept{

}



template<typename T>
BIterator<T> BTree<T>::BNode::find(const T &key) {
    int i = 0;
    while (i < keys.size() && key > keys[i])
        i++;

    if (keys[i] == key)
        return BIterator<T>(IterationBNode(this, i), std::make_shared<ForwardIteration<T>>());

    if (is_leaf)
        return BIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());

    return children[i]->find(key);
}


template<typename T>
BIterator<T> BTree<T>::find(const T &key) const noexcept{

    if (std::dynamic_pointer_cast<BNode>(Tree<T>::root)->data == key){
        return BIterator<T>(std::dynamic_pointer_cast<BNode>(Tree<T>::root), std::make_shared<ForwardIteration<T>>());
    }


    std::shared_ptr<BNode> temp = nullptr;

    if (std::dynamic_pointer_cast<BNode>(Tree<T>::root)->data > key){
        temp = std::dynamic_pointer_cast<BNode>(Tree<T>::root)->left;
    } else {
        temp = std::dynamic_pointer_cast<BNode>(Tree<T>::root)->right;
    }


    while (temp != nullptr){
        if (temp->data == key){
            return BIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
        } else if (temp->data > key){
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    return BIterator<T>(nullptr, std::shared_ptr<ForwardIteration<T>>());
}

template<typename T>
void BTree<T>::BNode::print() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!is_leaf)
            children[i]->print();
        std::cout << keys[i] << " ";
    }

    if (!is_leaf)
        children[i]->print();
}


template<typename T>
void BTree<T>::print() const noexcept {
    if(Tree<T>::root) {
        auto temp_root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        temp_root->print();
    }
}

template<typename T>
BIterator<T> BTree<T>::begin() const noexcept {
    auto temp = std::dynamic_pointer_cast<IterationBNode>(Tree<T>::root);
    temp->index = 0;

    while (temp->previous() != nullptr){
        temp = std::dynamic_pointer_cast<IterationBNode>(temp->previous());
    }

    return BIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BIterator<T> BTree<T>::end() const noexcept {
    return BIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BIterator<T> BTree<T>::rbegin() const noexcept {
    auto temp = std::dynamic_pointer_cast<IterationBNode>(Tree<T>::root);
    temp->index = 0;

    while(temp->next() != nullptr){
        temp = std::dynamic_pointer_cast<IterationBNode>(temp->next());
    }

    return BIterator<T>(temp, std::make_shared<ReverseIteration<T>>());
}

template<typename T>
BIterator<T> BTree<T>::rend() const noexcept {
    return BIterator<T>(nullptr, std::make_shared<ReverseIteration<T>>());
}

template<typename T>
BTree<T>::BTree(int _min_degree) : Tree<T>(){
    min_degree = _min_degree;
}


template<typename T>
BTree<T>::BNode::BNode(bool _is_leaf) {
    is_leaf = _is_leaf;
    parent = nullptr;
    keys.reserve(2 * BTree<T>::min_degree - 1);
    children.reserve(2 * BTree<T>::min_degree);
}


template<typename T>
BTree<T>::IterationBNode::IterationBNode(std::shared_ptr<BNode> bnode, int _index) {
    this->keys = bnode->keys;
    this->children = bnode->children;
    this->is_leaf = bnode->is_leaf;
    index = _index;
}

template<typename T>
std::shared_ptr<typename Tree<T>::Node> BTree<T>::IterationBNode::next() const noexcept {
    if(this->is_leaf) {
        if(this->index == this->keys.size() - 1) {
            auto current = this;
            // move up until there is next value or root
            while(current->parent && current->parent->keys.size() == current->parent->index + 1) {
                current = current->parent;
            }
            if(current->parent)
                return current->parent;
            return nullptr;
        }
        return std::make_shared(IterationBNode(this, this->index + 1));
    }
    // Keep moving the left most node starting from children[index+1] until we reach a leaf
    auto current = this->children[this->index + 1];
    while (!current->is_leaf)
        current = current->children[0];

    // Return the first key of the leaf
    return std::make_shared(IterationBNode(current, 0));
}

template<typename T>
std::shared_ptr<typename Tree<T>::Node> BTree<T>::IterationBNode::previous() const noexcept {
    if(this->is_leaf) {
        if(this->index == 0) {
            auto current = this;
            // move up until there is prev value or root
            while(current->parent && current->parent->index == 0) {
                current = current->parent;
            }
            if(current->parent)
                return current->parent;
            return nullptr;
        }
        return std::make_shared(IterationBNode(this, this->index - 1));
    }
    auto current = this->children[this->index];
    while (!current->is_leaf)
        current = current->children[current->keys.size()];

    // Return the last key of the leaf
    return std::make_shared(IterationBNode(current, current->keys.size() - 1));
}


