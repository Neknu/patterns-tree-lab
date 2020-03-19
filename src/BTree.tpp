#include "BTree.h"
#include "Tree.h"

#include <iostream>


template<typename T>
void BTree<T>::insert(const T &key) {
    if (Tree<T>::root == nullptr) {
        Tree<T>::root = std::make_shared<BNode>(true);
        auto root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        root->keys.push_back(key);
    }
    else // If tree is not empty 
    {
        auto root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        // If root is full, then tree grows in height 
        if (root->keys.size() == 2 * min_degree - 1) {
            // Allocate memory for new root 
            auto new_root =  std::make_shared<BNode>(false);

            // Make old root as child of new root 
            new_root->children.push_back(root);

            // Split the old root and move 1 key to the new root 
            new_root->splitChild(0, root);

            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0;
            if (new_root->keys[0] < key)
                i++;
            new_root->children[i]->insertNonFull(key);

            // Change root 
            root = new_root;
        }
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(key);
    }
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
void BTree<T>::BNode::insertNonFull(const T &key) {
    // Initialize index as index of rightmost element
    int i = keys.size() - 1;


    if (is_leaf) {
        while (i >= 0 && keys[i] > key) {
            i--;
        }

        keys.insert(keys.begin() + i + 1, key);
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > key)
            i--;

        if (children.size() == 2 * min_degree - 1) {

            splitChild(i+1, children[i+1]);

            if (keys[i+1] < key)
                i++;
        }
        children[i+1]->insertNonFull(key);
    }
}

template<typename T>
void BTree<T>::BNode::splitChild(int index, std::shared_ptr<BNode> child) {
    auto new_node = std::make_shared<BNode>(child->is_leaf);

    for (int j = 0; j < min_degree - 1; j++)
        new_node->keys.push_back(child->keys[j + min_degree]);

    if (!child->is_leaf) {
        for (int j = 0; j < min_degree; j++)
            new_node->children.push_back(child->children[j + min_degree]);
    }

    // Reduce the number of keys in y
    child->keys.resize(min_degree - 1);
    
    children.insert(children.begin() + index + 1, new_node);

    keys.insert(keys.begin() + index, child->keys[min_degree - 1]);
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
        return std::make_shared<IterationBNode>(this, this->index + 1);
    }
    // Keep moving the left most node starting from children[index+1] until we reach a leaf
    auto current = this->children[this->index + 1];
    while (!current->is_leaf)
        current = current->children[0];

    // Return the first key of the leaf
    return std::make_shared<IterationBNode>(current, 0);
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
        return std::make_shared<IterationBNode>(this, this->index - 1);
    }
    auto current = this->children[this->index];
    while (!current->is_leaf)
        current = current->children[current->keys.size()];

    // Return the last key of the leaf
    return std::make_shared<IterationBNode>(current, current->keys.size() - 1);
}


