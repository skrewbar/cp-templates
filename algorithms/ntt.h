#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll mod = 998244353;
constexpr ll root = 3;

ll power(ll base, ll exp) {
    ll res = 1;

    while (exp) {
        if (exp & 1)
            res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }

    return res;
}

void ntt(vector<ll>& x, bool inverse = false) {
    int r = inverse ? power(root, mod - 2) : root;
    int n = x.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;

        j |= bit;
        if (i < j)
            swap(x[i], x[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll angle = power(r, (mod - 1) / len);
        ll w = 1;

        for (int i = 0; i < n; i += len) {
            w = 1;
            for (int j = 0; j < (len >> 1); j++) {
                ll even = x[i | j];
                ll odd = x[i | j | len >> 1] * w % mod;
                x[i | j] = (even + odd) % mod;
                x[i | j | len >> 1] = (even - odd + mod) % mod;
                w = w * angle % mod;
            }
        }
    }

    if (inverse) {
        ll inv = power(n, mod - 2);
        for (auto& c : x)
            c = c * inv % mod;
    }
}