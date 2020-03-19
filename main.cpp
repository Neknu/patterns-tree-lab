#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
//    SplayTree<int> tree;
    BTree<int> tree(3);

//    BalancedTreeContext<int, SplayTree<int>> context(std::make_shared<SplayTree<int>>(tree));

    BalancedTreeContext<int, BTree<int>> context(std::make_shared<BTree<int>>(tree));



    return 0;
}