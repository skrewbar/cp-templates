#pragma once
#include <bits/stdc++.h>

namespace testy {
using TestFn = void (*)();
inline auto& registry() {
    static std::vector<std::pair<std::string, TestFn>> r;
    return r;
}

struct Registrar {
    Registrar(const char* name, TestFn fn) {
        registry().emplace_back(name, fn);
    }
};

constexpr const char *GREEN = "\033[32m", *RED = "\033[31m", *RESET = "\033[0m";

inline void RUN_ALL_TESTS() {
    int pass = 0, fail = 0;

    for (auto& [name, fn] : registry()) {
        try {
            fn();
            std::println("{}[PASS]{} {}", GREEN, RESET, name);
            ++pass;
        } catch (const std::exception& e) {
            std::println("{}[FAIL]{} {} - {}", RED, RESET, name, e.what());
            ++fail;
        }
    }

    std::println("\n--- {} tests | {}{}{} passed | {}{}{} failed ---", pass + fail,
                 GREEN, pass, RESET, RED, fail, RESET);
}
}  // namespace test

#define TEST(suite, name)                                            \
    class suite##_##name##_Test {                                    \
       private:                                                      \
        static void test();                                          \
        static inline testy::Registrar _reg{#suite "." #name, &test}; \
    };                                                               \
                                                                     \
    void suite##_##name##_Test::test()

template <typename... Args>
void ensuref(bool cond, std::format_string<Args...> fmt, Args&&... args) {
    if (!cond)
        throw std::runtime_error(std::format(fmt, std::forward<Args>(args)...));
}