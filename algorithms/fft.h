#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

void fft(vector<complex<double>>& x, bool inverse = false) {
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
        double angle = 2 * pi / len * (inverse ? -1 : 1);
        complex<double> root(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < (len >> 1); j++) {
                complex even = x[i | j];
                complex odd = x[i | j | len >> 1] * w;
                x[i | j] = even + odd;
                x[i | j | len >> 1] = even - odd;
                w *= root;
            }
        }
    }

    if (inverse)
        for (auto& c : x)
            c /= n;
}