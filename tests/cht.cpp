#include "cht.h"
#include "testy.h"

// gcd test
TEST(gcd, test) {
    i128 a = 12, b = 9;
    expect_eq(gcd(a, b), 3);
}

// Fraction tests
TEST(Fraction, negativeNumber) {
    Fraction f(-1, 1);
    expectf(f.numer < 0, "Expected numerator to be less than 0 but got {}",
            f.numer);
    expectf(f.denom > 0, "Expected denominator to be greater than 0 but got {}",
            f.denom);

    f = {1, -1};
    expectf(f.numer < 0, "Expected numerator to be less than 0 but got {}",
            f.numer);
    expectf(f.denom > 0, "Expected denominator to be greater than 0 but got {}",
            f.denom);
}
TEST(Fraction, reducing) {
    Fraction f(12, 9);
    expect_eq(f.numer, 4);
    expect_eq(f.denom, 3);
}
TEST(Fraction, less) {
    Fraction a(3, 2), b(5, 3);
    expectf(a < b, "Expected {}/{} to be less than {}/{} but got false",
            a.numer, a.denom, b.numer, b.denom);
    expectf(not(a < a), "Expected {}/{} to be not less than itself but it was",
            a.numer, a.denom);
}
TEST(Fraction, lessOrEq) {
    Fraction a(3, 2), b(5, 3);
    expectf(a <= b,
            "Expected {}/{} to be less than or equal to {}/{} but got false",
            a.numer, a.denom, b.numer, b.denom);
    expectf(a <= a,
            "Expected {}/{} to be less than or equal to itself but it wasn't",
            a.numer, a.denom);
}
TEST(Fraction, multiply) {
    Fraction a(5, 2);
    Fraction b = a * 2;

    expectf(b.numer == 5 and b.denom == 1,
            "Expected {}/{} times 2 to be 5/1 but got {}/{}", a.numer, a.denom,
            b.numer, b.denom);
    a *= 2;
    expectf(b.numer == a.numer and b.denom == a.denom,
            "Expected results of * and *= to be equal but it wasn't");
}
TEST(Fraction, add) {
    Fraction a(5, 2);
    Fraction b = a + 2;

    expectf(b.numer == 9 and b.denom == 2,
            "Expected {}/{} add 2 to be 9/2 but got {}/{}", a.numer, a.denom,
            b.numer, b.denom);
    a += 2;
    expectf(b.numer == a.numer and b.denom == a.denom,
            "Expected results of + and += to be equal but it wasn't");
}

// Line test
TEST(Line, intersection) {
    Line a = {3, 2}, b = {7, 3};
    Fraction inter = a.getIntersection(b);

    expectf(inter.numer == -1 and inter.denom == 4,
            "Expected -1/4 but got {}/{}", inter.numer, inter.denom);
}

// LineContainer tests
TEST(LineContainer, push) {
    LineContainer container(0);
    container.push(Line(7, 3));
    container.push(Line(3, 2));

    Fraction start = container.lines.back().start;
    expectf(start.numer == -1 and start.denom == 4,
            "Expected start to be -1/4 but got {}/{}", start.numer,
            start.denom);
}

TEST(LineContainer, flush) {
    LineContainer container(10);
    container.push(Line(3, 2));
    container.push(Line(1, 3));
    container.flush();

    for (int i = 1; i < container.lines.size(); i++)
        expectf(container.lines[i - 1].slope > container.lines[i].slope,
                "Expected the slopes to be decrease but it wasn't");

    container.push(Line(5, 3));
    container.push(Line(2, 7));
    container.flush();

    for (int i = 1; i < container.lines.size(); i++)
        expectf(container.lines[i - 1].slope > container.lines[i].slope,
                "Expected the slopes to be decrease but it wasn't");
}

TEST(LineContainer, query) {
    LineContainer container(0);

    vector<Line> lines = {{3, 2}, {7, 3}, {5, 1}};

    for (const Line& l : lines)
        container.push(l);

    for (int i = -100; i <= 100; i++) {
        Fraction maximum = LLONG_MIN;
        for (const Line& l : lines)
            maximize(maximum, Fraction(l.slope * i + l.yinter));

        Fraction queryResult = container.query(i);
        expectf(queryResult.numer == maximum.numer and
                    queryResult.denom == maximum.denom,
                "Expected query({}) to be {}/{} but got {}/{}", i,
                maximum.numer, maximum.denom, queryResult.numer,
                queryResult.denom);
    }
}

int main() {
    testy::RUN_ALL_TESTS();
}