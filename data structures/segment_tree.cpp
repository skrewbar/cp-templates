#include "testy.h"
using namespace std;

template <typename T, typename Merger>
struct SegmentTree {
    Merger merge = Merger();

    int n;
    vector<T> t;

    SegmentTree(int _n) : n(1 << (int)ceil(log2(_n))), t(n << 1) {}

    void update(int i, T v) {
        t[i += n] = v;

        while (i >>= 1)
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    T query(int l, int r) {
        T ret = T();

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = merge(t[l++], ret);
            if (~r & 1)
                ret = merge(ret, t[r--]);
        }

        return ret;
    }
};

const int sz = 10;
const int actualSz = 1 << (int)ceil(log2(sz));
struct Adder {
    int operator()(int a, int b) { return a + b; }
};

TEST(seg, update) {
    SegmentTree<int, Adder> seg(sz);

    seg.update(3, 3);
    ensuref(seg.t[3 + actualSz] == 3, "(1) update leaf node failed");
    ensuref(seg.t[1] == 3, "(2) update parent node failed");

    seg.update(6, 7);
    ensuref(seg.t[6 + actualSz] == 7, "(3) update leaf node failed");
    ensuref(seg.t[1] == 10, "(4) update parent node failed");
}

TEST(seg, query) {
    SegmentTree<int, Adder> seg(sz);

    seg.update(3, 3);
    seg.update(5, 2);
    seg.update(6, 7);

    ensuref(seg.query(0, sz - 1) == 12, "query [0, {}] failed", sz - 1);
    ensuref(seg.query(0, 4) == 3, "query [0, 4] failed");
    ensuref(seg.query(2, 5) == 5, "query [2, 5] failed");
    ensuref(seg.query(4, 7) == 9, "query [4, 7] failed");
}

TEST(seg, add) {
    SegmentTree<int, Adder> seg(5);
    for (int i = 0; i < 5; i++)
        seg.update(i, i + 1);

    seg.update(2, 6);
    ensuref(seg.query(1, 4) == 17, "query 1 failed");
    seg.update(4, 2);
    ensuref(seg.query(2, 4) == 12, "query 2 failed");
}

int main() {
    test::RUN_ALL_TESTS();
}