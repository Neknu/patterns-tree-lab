#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
    SplayTree<int> tree;
    tree.insert(4);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(1);
    tree.insert(8);
    tree.insert(2);
    tree.insert(3);
    //tree.print();

    auto iter = tree.find(1);

    for (auto i = tree.rbegin(); i != tree.rend(); ++i){
        std::cout << *i;
    }




    return 0;
}