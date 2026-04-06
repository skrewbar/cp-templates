#include "segment_tree.h"
#include "testy.h"

const int sz = 10;
const int actualSz = 1 << (int)ceil(log2(sz));
struct Adder {
    int operator()(int a, int b) { return a + b; }
};

TEST(SegmentTree, update) {
    SegmentTree<int, Adder> seg(sz);

    seg.update(3, 3);
    ensuref(seg.t[3 + actualSz] == 3,
            "Expected the leaf node to be 3 but got {}", seg.t[3 + actualSz]);
    ensuref(seg.t[1] == 3, "Expected the root node to be 3 but got {}",
            seg.t[1]);

    seg.update(6, 7);
    ensuref(seg.t[6 + actualSz] == 7,
            "Expected the leaf node to be 7 but got {}", seg.t[6 + actualSz]);
    ensuref(seg.t[1] == 10, "Expected the root node to be 10 but got {}",
            seg.t[1]);
}

TEST(SegmentTree, query) {
    SegmentTree<int, Adder> seg(sz);

    seg.update(3, 3);
    seg.update(5, 2);
    seg.update(6, 7);

    int q = seg.query(0, sz - 1);
    ensuref(q == 12, "Expected query [0, {}] to be 12 but got {}", sz - 1, q);
    q = seg.query(0, 4);
    ensuref(q == 3, "Expected query [0, 4] to be 3 but got {}", q);
    q = seg.query(2, 5);
    ensuref(q == 5, "Expected query [2, 5] to be 5 but got {}", q);
    q = seg.query(4, 7);
    ensuref(q == 9, "Expected query [4, 7] to be 9 but got {}", q);
}

int main() {
    test::RUN_ALL_TESTS();
}