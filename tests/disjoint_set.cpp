#include "disjoint_set.h"
#include "testy.h"

TEST(DisjointSet, all) {
    DisjointSet ds(5);

    ds.unionParent(0, 1);
    ensuref(ds.isConnected(0, 1), "0 and 1 should be connected");

    ds.unionParent(0, 3);
    ensuref(ds.isConnected(0, 3), "0 and 3 should be connected");
    ensuref(ds.isConnected(1, 3), "1 and 3 should be connected");
}

int main() {
    testy::RUN_ALL_TESTS();
}