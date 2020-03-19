#include "BIterator.hpp"
#include "Tree.h"

#include <iostream>

template<typename T>
BIterator<T>::BIterator(
        std::shared_ptr<typename BTree<T>::IterationBNode> root,
        std::shared_ptr<IterationPolicy<T>> policy
)
        : curr_node(root), policy(policy){}


template<typename T>
BIterator<T>& BIterator<T>::operator++() noexcept {
    if (curr_node != nullptr){
        curr_node = std::dynamic_pointer_cast<typename BTree<T>::IterationBNode>(policy->next(curr_node));
    }

    return *this;
}


template<typename T>
BIterator<T> BIterator<T>::operator+(int n) const noexcept {
    auto temp = curr_node;
    for (int i = 0; i < n; ++i){
        if (temp == nullptr){
            break;
        }
        temp = std::dynamic_pointer_cast<typename BTree<T>::IterationBNode>(policy->next(curr_node));
    }
    return BIterator(temp, policy);
}


template<typename T>
const T& BIterator<T>::operator*() const noexcept {
    return curr_node->keys[curr_node->index];
}

template<typename T>
bool BIterator<T>::operator!=(const BIterator &other) noexcept {
    return curr_node != other.curr_node;
}

template<typename T>
bool BIterator<T>::operator==(const BIterator &other) noexcept {
    return curr_node == other.curr_node;
}



