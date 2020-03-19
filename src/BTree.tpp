#include "BTree.h"
#include "Tree.h"

//template<typename T>
//BTree<T>::BTree(int _min_degree) {
//    min_degree = _min_degree;
//    this->root = nullptr;
//}
//
//template<typename T>
//BTree<T>::~BTree() {
//    delete Tree<T>::root;
//}
//
//template<typename T>
//BTree<T>::BNode::BNode(bool _is_leaf) {
//    is_leaf = _is_leaf;
//
//    keys.reserve(2 * BTree<T>::min_degree - 1);
//    children.reserve(2 * BTree<T>::min_degree);
//}
//
//template<typename T>
//void BTree<T>::BNode::print() {
//    int i;
//    for (i = 0; i < keys.size(); i++) {
//        if (!is_leaf)
//            children[i]->traverse();
//        std::cout << keys[i] << " ";
//    }
//
//    if (!is_leaf)
//        children[i]->traverse();
//}
//
//template<typename T>
//void BTree<T>::print() const noexcept {
//    if(Tree<T>::root) {
//        auto temp_root = dynamic_cast<BNode *>(Tree<T>::root);
//        temp_root->print();
//    }
//}
//
//template<typename T>
//BaseIterator<T> BTree<T>::find(const T &key) const {
//    if(Tree<T>::root) {
//        auto temp_root = dynamic_cast<BNode *>(Tree<T>::root);
//        temp_root->find(key);
//    }
//}
//
////template<typename T>
////void BTree<T>::print() const noexcept {
////    for (auto i = Tree<T>::begin(); i != Tree<T>::end(); ++i){
////        std::cout << *i << " ";
////    }
////}
//
//template<typename T>
//BaseIterator<T> BTree<T>::BNode::find(const T &key) {
//    int i = 0;
//    while (i < keys.size() && key > keys[i])
//        i++;
//
//    if (keys[i] == key)
//        return BaseIterator<T>(FindBNode(this, i), std::make_shared<ForwardIteration<T>>());
//
//    if (is_leaf)
//        return BaseIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
//
//    return children[i]->find(key);
//}
//
//template<typename T>
//BTree<T>::FindBNode::FindBNode(BTree::BNode* bnode, int _index) {
//    this->keys = bnode->keys;
//    this->children = bnode->children;
//    this->is_leaf = bnode->is_leaf;
//    index = _index;
//}
