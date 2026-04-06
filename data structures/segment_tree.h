#include <bits/stdc++.h>
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

