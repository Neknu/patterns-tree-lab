#pragma once


#include "Tree.h"
#include "BIterator.hpp"
#include <vector>

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
    static int min_degree;

    class IterationBNode;

    class BNode : public Tree<T>::Node {
    public:
        explicit BNode(bool is_leaf);
        ~BNode() {
            keys.clear();
            children.clear();
        }

        void print();
        BIterator<T> find(const T& key);

        void insertNonFull(const T& key);

        // A utility function to split the child `child` of this node. `index` is index of child in
        // child array children[].  The Child y must be full when this function is called
        void splitChild(int index, std::shared_ptr<BNode> child);

    public:
        std::vector<T> keys;
        std::vector<std::shared_ptr<BNode>> children;
        bool is_leaf;
        std::shared_ptr<IterationBNode> parent;
    };

    class IterationBNode: public BNode {
    public:
        // index of current key in BNode
        int index;
    public:
        IterationBNode(std::shared_ptr<BNode> bnode, int _index);
        std::shared_ptr<typename Tree<T>::Node> next() const noexcept override;
        std::shared_ptr<typename Tree<T>::Node> previous() const noexcept override;
    };
};

#include "BTree.tpp"

// #pragma once
//
//#include "Tree.h"
//
//#include <vector>
//
///**
//* @brief Class for implementing BTree
//*/
//template<typename T>
//class BTree : public Tree<T> {
//private:
//    int min_degree;
//
//    class BNode : public Tree<T>::Node {
//    protected:
//        std::vector<T> keys;
//        std::vector<BNode*> children;
//        bool is_leaf;
//    public:
//        BNode(bool is_leaf);
//        ~BNode() {
//            keys.clear();
//            children.clear();
//        }
//
//        void print();
//
//        BaseIterator<T> find(const T& key);
//
//    };
//
//    class FindBNode: public BNode {
//    private:
//        int index;
//    public:
//        // index of current key in BNode
//        FindBNode(BNode* bnode, int index);
//        ~FindBNode() {
//            this->keys.clear();
//            this->children.clear();
//        }
//    };
//
//public:
//    BTree(int min_degree);
//    ~BTree() override;
//
//    void insert(const T& key) override;
//    void remove(const T& key) override;
//    BaseIterator<T> find(const T& key) const override;
//
//    void print() const noexcept override;
//
//};
//
//#include "BTree.tpp"

