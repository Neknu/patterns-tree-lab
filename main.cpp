#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
//    SplayTree<int> tree;
    BTree<int> tree(3);
    tree.insert(4);
    tree.insert(499);
    tree.insert(5);
    tree.insert(11);
    tree.insert(12);
    tree.insert(14);
    tree.insert(23);
    tree.insert(12);
    tree.insert(14);
    tree.insert(444);
    tree.insert(12);
    tree.insert(14);
    std::cout << "dddd" << tree.find(444).operator*();
    tree.print();

//    BalancedTreeContext<int, SplayTree<int>> context(std::make_shared<SplayTree<int>>(tree));

    BalancedTreeContext<int, BTree<int>> context(std::make_shared<BTree<int>>(tree));


    return 0;
}