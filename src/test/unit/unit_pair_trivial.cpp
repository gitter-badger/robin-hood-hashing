#include <robin_hood.h>

#include <app/doctest.h>

#include <iostream>
#include <string>
#include <type_traits>

template <typename K, typename V>
using TestPair = robin_hood::pair<K, V>;

template <typename K, typename V>
void nothrow_trivially() {
    static_assert(std::is_nothrow_move_constructible<TestPair<K, V>>::value ==
                      // cppcheck-suppress duplicateExpression
                      (std::is_nothrow_move_constructible<K>::value &&
                       std::is_nothrow_move_constructible<V>::value),
                  "pair doesnt have same attributes as key & value");

    static_assert(std::is_nothrow_move_assignable<TestPair<K, V>>::value ==
                      // cppcheck-suppress duplicateExpression
                      (std::is_nothrow_move_assignable<K>::value &&
                       std::is_nothrow_move_assignable<V>::value),
                  "pair doesnt have same attributes as key & value");

    static_assert(ROBIN_HOOD_IS_TRIVIALLY_COPYABLE(TestPair<K, V>) ==
                      (ROBIN_HOOD_IS_TRIVIALLY_COPYABLE(K) && ROBIN_HOOD_IS_TRIVIALLY_COPYABLE(V)),
                  "pair doesnt have same attributes as key & value");

    static_assert(
        std::is_trivially_destructible<TestPair<K, V>>::value ==
            (std::is_trivially_destructible<K>::value && std::is_trivially_destructible<V>::value),
        "pair doesnt have same attributes as key & value");

    static_assert(sizeof(TestPair<K, V>) == sizeof(std::pair<K, V>),
                  "pair doesnt have same attributes as key & value");
}

TEST_CASE("pair trivially copy/destructible") {
    nothrow_trivially<int, int>();
    nothrow_trivially<float, float>();
    nothrow_trivially<size_t, std::string>();
    nothrow_trivially<std::string, size_t>();
    nothrow_trivially<char const*, size_t>();
    nothrow_trivially<size_t, char const*>();
    nothrow_trivially<uint64_t, uint64_t>();
    nothrow_trivially<uint32_t, uint32_t>();
    nothrow_trivially<char, char>();
}

TEST_CASE("pairstuff") {
    robin_hood::pair<std::string, std::string> p("asdf", "321");
    auto pc = p;
    p = pc;
    p = std::move(pc);

    std::string a = "13";
    std::string b = "54";
    robin_hood::pair<std::string, std::string> p2(std::move(a), std::move(b));

    using std::swap;
    swap(p, p2);
}
