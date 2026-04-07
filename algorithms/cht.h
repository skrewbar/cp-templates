#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) \
    sort(all(v));   \
    v.erase(unique(all(v)), (v).end())

template <typename T>
bool minimize(T& target, T value) {
    return target > value ? (target = value, true) : false;
}
template <typename T>
bool maximize(T& target, T value) {
    return target < value ? (target = value, true) : false;
}

using ll = long long;
using i128 = __int128;

i128 gcd(i128 a, i128 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

struct Fraction {
    i128 numer, denom;

    Fraction(ll _numer, ll _denom) : numer(_numer), denom(_denom) {
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }

        reduce();
    }
    Fraction(ll a) : numer(a), denom(1) {}

    void reduce() {
        bool isNegative = numer < 0;

        if (isNegative)
            numer = -numer;

        i128 g = gcd(numer, denom);
        numer /= g;
        denom /= g;

        if (isNegative)
            numer = -numer;
    }

    bool operator<(const Fraction& frac) const {
        return (numer * frac.denom) < (frac.numer * denom);
    }
    bool operator<=(const Fraction& frac) const {
        return (numer * frac.denom) <= (frac.numer * denom);
    }

    Fraction& operator*=(const ll a) {
        numer *= a;
        reduce();
        return *this;
    }
    Fraction operator*(const ll a) const {
        Fraction ret(*this);
        ret *= a;
        return ret;
    }
    Fraction& operator+=(const ll a) {
        numer += denom * a;
        reduce();
        return *this;
    }
    Fraction operator+(const ll a) const {
        Fraction ret(*this);
        ret += a;
        return ret;
    }
};

struct Line {
    ll slope, yinter;
    Fraction start;

    Line(ll _slope, ll _yinter)
        : slope(_slope), yinter(_yinter), start(LLONG_MIN, 1) {}

    Fraction getIntersection(const Line& l) {
        return Fraction(l.yinter - yinter, slope - l.slope);
    }
};

struct LineContainer {
    size_t bufferSize;
    vector<Line> lines, buffer;

    LineContainer(size_t _bufferSize) : bufferSize(_bufferSize) {
        buffer.reserve(bufferSize);
    }

    void push(Line l) {
        while (not lines.empty()) {
            const Line& back = lines.back();

            if (l.slope > back.slope) {
                buffer.push_back(l);
                return;
            }

            if (l.slope == back.slope) {
                if (l.yinter > back.yinter) {
                    lines.pop_back();
                    continue;
                }
                return;
            }

            l.start = l.getIntersection(back);
            if (l.start <= back.start)
                lines.pop_back();
            else
                break;
        }

        lines.push_back(l);
    }

    void flush() {
        sort(all(buffer), [](const Line& l1, const Line& l2) {
            return l1.slope > l2.slope;
        });

        vector<Line> oldMain;
        swap(oldMain, lines);

        int i = 0, j = 0;
        while (i < (int)oldMain.size() and j < (int)buffer.size()) {
            if (oldMain[i].slope > buffer[j].slope)
                push(oldMain[i++]);
            else
                push(buffer[j++]);
        }

        while (i < (int)oldMain.size())
            push(oldMain[i++]);
        while (j < (int)buffer.size())
            push(buffer[j++]);

        buffer.clear();
    }

    Fraction query(const Fraction& x) {
        const Line& l0 = *(upper_bound(all(lines), x,
                                       [](const Fraction& x, const Line& l) {
                                           return x < l.start;
                                       }) -
                           1);

        Fraction ret = x * l0.slope + l0.yinter;
        for (const Line& l : buffer)
            maximize(ret, x * l.slope + l.yinter);

        return ret;
    }
};
