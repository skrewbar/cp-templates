#include "fft.h"
#include "testy.h"

TEST(fft, convolution) {
    vector<complex<double>> a = {1, 2, 3};
    vector<complex<double>> b = {4, 5, 6};

    int n = 1 << (int)ceil(log2(a.size() + b.size() - 1));
    a.resize(n);
    b.resize(n);

    fft(a);
    fft(b);

    vector<complex<double>> res(n);
    for (int i = 0; i < n; i++)
        res[i] = a[i] * b[i];
    fft(res, true);

    vector<int> expected = {4, 13, 28, 27, 18};
    for (int i = 0; i < n; i++) {
        if (i < expected.size())
            ensuref(round(res[i].real()) == expected[i], "Expected {}, got {}",
                    expected[i], round(res[i].real()));
        else
            ensuref(round(res[i].real()) == 0, "Expected 0, got {}",
                    round(res[i].real()));
    }
}

int main() {
    testy::RUN_ALL_TESTS();
}