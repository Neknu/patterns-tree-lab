template<typename T>
BaseIterator<T>::BaseIterator(
        typename Tree<T>::BaseNode *root,
        const IterationPolicy<T> &policy
)
        : curr_node(root), policy(policy){}


template<typename T>
BaseIterator<T>& BaseIterator<T>::operator++() noexcept {
    curr_node = policy.next(curr_node);
    return *this;
}


template<typename T>
BaseIterator<T>& BaseIterator<T>::operator+(int n) noexcept {
    for (int i = 0; i < n; ++i){
        curr_node = policy.next(curr_node);
    }
    return *this;
}


template<typename T>
BaseIterator<T>& ForwardIteration<T>::next(typename Tree<T>::BaseNode* node) {
    return node->next();
}


template<typename T>
BaseIterator<T>& ReverseIteration<T>::next(typename Tree<T>::BaseNode* node) {
    return node->previous();
}