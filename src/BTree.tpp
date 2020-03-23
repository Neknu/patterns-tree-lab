#include "BTree.h"
#include "Tree.h"

#include <iostream>


template<typename T>
void BTree<T>::insert(const T &key) {
    if (Tree<T>::root == nullptr) {
        Tree<T>::root = std::make_shared<BNode>(true, min_degree);
        auto root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        root->keys.push_back(key);
    }
    else // If tree is not empty 
    {
        auto root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        // If root is full, then tree grows in height 
        if (root->keys.size() == 2 * min_degree - 1) {
            // Allocate memory for new root 
            auto new_root =  std::make_shared<BNode>(false, min_degree);

            // Make old root as child of new root 
            new_root->children.push_back(root);

            root->parent = new_root;
            // Split the old root and move 1 key to the new root 
            new_root->splitChild(0, root);

            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0;
            if (new_root->keys[0] < key)
                i++;
            new_root->children[i]->insertNonFull(key);

            // Change root 
            Tree<T>::root = new_root;
        }
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(key);
    }
}



template<typename T>
void BTree<T>::remove(const T &key) noexcept{

}

template<typename T>
BIterator<T> BTree<T>::find(const T &key) const noexcept{
    if(Tree<T>::root) {
        auto temp_root = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
        return temp_root->findIterator(key);
    }
    return BIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
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
    auto temp = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
    temp->index = 0;

    while (temp->previous() != nullptr){
        temp = std::dynamic_pointer_cast<BNode>(temp->previous());
    }

    return BIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BIterator<T> BTree<T>::end() const noexcept {
    return BIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BIterator<T> BTree<T>::rbegin() const noexcept {
    auto temp = std::dynamic_pointer_cast<BNode>(Tree<T>::root);
    temp->index = 0;

    while(temp->next() != nullptr){
        temp = std::dynamic_pointer_cast<BNode>(temp->next());
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
int BTree<T>::BNode::getParentIndex() {
    auto child = this->shared_from_this();
    if(!child->parent) return -1;

    int counter = 0;
    for(auto elem:child->parent->children) {
        if(elem == child)
            return counter;
        counter++;
    }
    return -1;
}

template<typename T>
std::shared_ptr<typename BTree<T>::BNode> BTree<T>::BNode::find(int key) {
    int i = 0;
    auto current = this->shared_from_this();
    while (i < current->keys.size() && key > current->keys[i])
        i++;

    if (current->keys[i] == key) {
        current->index = i;
        return current;
    }


    if (current->is_leaf)
        return nullptr;

    return current->children[i]->find(key);
}

template<typename T>
BIterator<T> BTree<T>::BNode::findIterator(const T &key) {
    return BIterator<T>(this->find(key), std::make_shared<ForwardIteration<T>>());
}


template<typename T>
BTree<T>::BNode::BNode(bool _is_leaf, int _min_degree) {
    index = -1;
    is_leaf = _is_leaf;
    parent = nullptr;
    min_degree = _min_degree;
    keys.reserve(2 * min_degree - 1);
    children.reserve(2 * min_degree);
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

        if (children[i + 1]->keys.size() == 2 * min_degree - 1) {

            splitChild(i+1, children[i+1]);

            if (keys[i+1] < key)
                i++;
        }
        children[i+1]->insertNonFull(key);
    }
}

template<typename T>
void BTree<T>::BNode::splitChild(int ind, std::shared_ptr<BNode> child) {
    auto new_node = std::make_shared<BNode>(child->is_leaf, child->min_degree);

    for (int j = 0; j < min_degree - 1; j++)
        new_node->keys.push_back(child->keys[j + min_degree]);

    if (!child->is_leaf) {
        for (int j = 0; j < min_degree; j++)
            new_node->children.push_back(child->children[j + min_degree]);
    }

    // Reduce the number of keys in y
    child->keys.resize(min_degree - 1);
    children.insert(children.begin() + ind + 1, new_node);
    new_node->parent = child->parent;

    keys.insert(keys.begin() + ind, child->keys[min_degree - 1]);
}

template<typename T>
std::shared_ptr<typename Tree<T>::Node> BTree<T>::BNode::next() noexcept {
    if(this->is_leaf) {
        if(this->index == this->keys.size() - 1  && this->parent) {
            auto current = this->shared_from_this();
            // move up until there is prev value or root
            while(current->parent && current->parent->keys.size() == current->getParentIndex()) {
                current = current->parent;
            }
            if(current->parent) {
                current->parent->index = current->getParentIndex();
                return current->parent;
            }
            return nullptr;
        }
        auto current = this->shared_from_this();
        current->index += 1;
        return current;
    }
    auto current = this->children[this->index + 1];
    while (!current->is_leaf)
        current = current->children[0];

    current->index = 0;
    return current;
}

template<typename T>
std::shared_ptr<typename Tree<T>::Node> BTree<T>::BNode::previous() noexcept {
    if(this->is_leaf) {
        if(this->index == 0 && this->parent) {
            auto current = this->shared_from_this();
            // move up until there is prev value or root
            while(current->parent && current->getParentIndex() == 0) {
//            while(current->parent) {
                current = current->parent;
            }
            if(current->parent) {
                current->parent->index = current->getParentIndex();
                return current->parent;
            }
            return nullptr;
        }
        auto current = this->shared_from_this();
        current->index -= 1;
        return current;
    }
    auto current = this->children[this->index];
    while (!current->is_leaf)
        current = current->children[current->keys.size()];

    // Return the last key of the leaf
    current->index = current->keys.size() - 1;
    return current;
}

template<typename T>
int BTree<T>::BNode::findKey(int key) {
    int idx=0;
    while (idx < keys.size() && keys[idx] < key)
        ++idx;
    return idx;
}

