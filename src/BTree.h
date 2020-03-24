#pragma once


#include "Tree.h"
#include "BIterator.hpp"
#include <vector>
#include <memory>

/**
* @brief Class for implementing B Tree
*/
template<typename T>
class BTree : public Tree<T> {
public:
    class BNode;
public:
    explicit BTree(int min_degree);

    void insert(const T& key) override;
    void remove(const T& key) noexcept override;
    void print() const noexcept override;

    BIterator<T> find(const T& key) const noexcept;
    BIterator<T> begin() const noexcept;
    BIterator<T> end() const noexcept;
    BIterator<T> rbegin() const noexcept;
    BIterator<T> rend() const noexcept;

public:
    int min_degree;

class BNode : public std::enable_shared_from_this<BNode>, public Tree<T>::Node {
    public:
        explicit BNode(bool is_leaf, int min_degree);
        ~BNode() {
            keys.clear();
            children.clear();
        }

        std::shared_ptr<typename Tree<T>::Node> next() noexcept override;
        std::shared_ptr<typename Tree<T>::Node> previous() noexcept override;

        void print();

        void insertNonFull(const T& key);

        BIterator<T> findIterator(const T& key);

        int getParentIndex();

        // A function to search a key in subtree rooted with this node.
        std::shared_ptr<BNode> find(T key);   // returns NULL if k is not present.

        // A function that returns the index of the first key that is greater
        // or equal to k
        int findKey(T key);

        // A wrapper function to remove the key k in subtree rooted with
        // this node.
        void remove(T key);

        // A function to remove the key present in idx-th position in
        // this node which is a leaf
        void removeFromLeaf(int idx);

        // A function to remove the key present in idx-th position in
        // this node which is a non-leaf node
        void removeFromNonLeaf(int idx);

        // A function to get the predecessor of the key- where the key
        // is present in the idx-th position in the node
        T getPred(int idx);

        // A function to get the successor of the key- where the key
        // is present in the idx-th position in the node
        T getSucc(int idx);

        // A function to fill up the child node present in the idx-th
        // position in the C[] array if that child has less than t-1 keys
        void fill(int idx);

        // A function to borrow a key from the C[idx-1]-th node and place
        // it in C[idx]th node
        void borrowFromPrev(int idx);

        // A function to borrow a key from the C[idx+1]-th node and place it
        // in C[idx]th node
        void borrowFromNext(int idx);

        // A function to merge idx-th child of the node with (idx+1)th child of
        // the node
        void merge(int idx);

    // A utility function to split the child `child` of this node. `index` is index of child in
        // child array children[].  The Child y must be full when this function is called
        void splitChild(int index, std::shared_ptr<BNode> child);

    public:
        std::vector<T> keys;
        std::vector<std::shared_ptr<BNode>> children;
        bool is_leaf;
        int min_degree;
        int index; // index of current key (-1 if it doesn't need)
        std::shared_ptr<BNode> parent;
    };
};

#include "BTree.tpp"
