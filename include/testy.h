#pragma once
#include <print>
#include <string>
#include <vector>

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
#define COLORED(text, color) std::format("{}{}{}", color, text, RESET)

template <typename First, typename... Args>
void print(First&& first, Args&&... args) {
    std::print("{}", first);
    (std::print(" {}", args), ...);
}

template <typename... Args>
void println(Args&&... args) {
    print(std::forward<Args>(args)...);
    std::println();
}

inline void RUN_ALL_TESTS() {
    int pass = 0, fail = 0;

    for (auto& [name, fn] : registry()) {
        try {
            fn();
            println(COLORED("[PASS]", GREEN), name);
            ++pass;
        } catch (const std::exception& e) {
            println(COLORED("[FAIL]", RED), name, "-", e.what());
            ++fail;
        }
    }

    std::println("\n--- {} tests | {} passed | {} failed ---", pass + fail,
                 COLORED(pass, GREEN), COLORED(fail, RED));
}
}  // namespace testy

#define TEST(suite, name)                                             \
    class suite##_##name##_Test {                                     \
       private:                                                       \
        static void test();                                           \
        static inline testy::Registrar _reg{#suite "." #name, &test}; \
    };                                                                \
                                                                      \
    void suite##_##name##_Test::test()

template <typename... Args>
void _expectf(int line,
              bool cond,
              std::format_string<Args...> fmt,
              Args&&... args) {
    if (!cond)
        throw std::runtime_error(
            std::format("Line {}: {}", line,
                        std::format(fmt, std::forward<Args>(args)...)));
}
#define expectf(...) _expectf(__LINE__, __VA_ARGS__)

template <typename T1, typename T2>
void _expect_eq(const T1& a, const T2& b, int line) {
    if (a != b)
        throw std::runtime_error(
            std::format("Line {}: Expected {}, got {}", line, a, b));
}
#define expect_eq(a, b) _expect_eq(a, b, __LINE__)