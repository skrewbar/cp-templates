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
    expect_eq(seg.t[3 + actualSz], 3);
    expect_eq(seg.t[1], 3);

    seg.update(6, 7);
    expect_eq(seg.t[6 + actualSz], 7);
    expect_eq(seg.t[1], 10);
}

TEST(SegmentTree, query) {
    SegmentTree<int, Adder> seg(sz);

    seg.update(3, 3);
    seg.update(5, 2);
    seg.update(6, 7);

    int q = seg.query(0, sz - 1);
    expect_eq(q, 12);
    q = seg.query(0, 4);
    expect_eq(q, 3);
    q = seg.query(2, 5);
    expect_eq(q, 5);
    q = seg.query(4, 7);
    expect_eq(q, 9);
}

int main() {
    testy::RUN_ALL_TESTS();
}