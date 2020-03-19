#include "SplayIterator.hpp"
#include "Tree.h"

#include <iostream>

template<typename T>
SplayIterator<T>::SplayIterator(
        std::shared_ptr<typename SplayTree<T>::SplayNode> root,
        std::shared_ptr<IterationPolicy<T>> policy
)
        : curr_node(root), policy(policy){}


template<typename T>
SplayIterator<T>& SplayIterator<T>::operator++() noexcept {
    if (curr_node != nullptr){
        curr_node = std::dynamic_pointer_cast<typename SplayTree<T>::SplayNode>(policy->next(curr_node));
    }

    return *this;
}


template<typename T>
SplayIterator<T> SplayIterator<T>::operator+(int n) const noexcept {
    auto temp = curr_node;
    for (int i = 0; i < n; ++i){
        if (temp == nullptr){
            break;
        }
        temp = std::dynamic_pointer_cast<typename SplayTree<T>::SplayNode>(policy->next(curr_node));
    }
    return SplayIterator(temp, policy);
}


template<typename T>
const T& SplayIterator<T>::operator*() const noexcept {
    return curr_node->data;
}

template<typename T>
bool SplayIterator<T>::operator!=(const SplayIterator &other) noexcept {
    return curr_node != other.curr_node;
}

template<typename T>
bool SplayIterator<T>::operator==(const SplayIterator &other) noexcept {
    return curr_node == other.curr_node;
}


template<typename T>
std::shared_ptr<typename Tree<T>::Node> ForwardIteration<T>::next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept{
    return node->next();
}


template<typename T>
std::shared_ptr<typename Tree<T>::Node> ReverseIteration<T>::next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept{
    return node->previous();
}