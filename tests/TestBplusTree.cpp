#include "../src/BplusTree.h"

#include "catch.hpp"

TEST_CASE("BplusTree tests", "[BplusTree]") {

    SECTION( "test" ) {
        BplusTree<int> t(7);

        for (int i = 0; i < 70; ++i)
            t.insert(i);
        t.print();

        for (int i = 69; i > -1; --i) {
            std::cout << "Remove " << i << '\n';
            t.remove(i);
        }
        t.print();

        system("pause");
    }
}
