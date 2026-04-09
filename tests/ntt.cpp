#include "ntt.h"
#include "testy.h"

TEST(ntt, convolution) {
    vector<ll> a = {1, 2, 3};
    vector<ll> b = {4, 5, 6};

    int n = 1 << (int)ceil(log2(a.size() + b.size() - 1));
    a.resize(n);
    b.resize(n);

    ntt(a);
    ntt(b);

    vector<ll> res(n);
    for (int i = 0; i < n; i++)
        res[i] = a[i] * b[i];
    ntt(res, true);

    vector<ll> expected = {4, 13, 28, 27, 18};
    for (int i = 0; i < n; i++) {
        if (i < expected.size())
            ensuref(res[i] == expected[i], "Expected {}, got {}", expected[i],
                    res[i]);
        else
            ensuref(res[i] == 0, "Expected 0, got {}", res[i]);
    }
}

int main() {
    testy::RUN_ALL_TESTS();
}