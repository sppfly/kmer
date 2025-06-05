#include "test.hpp"
#include <algorithm>
#include <iostream>

void test_simple() {
    // ACGCTG
    std::cout << "------test_simple------" << '\n';
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{1, 'A'}}},
        {1, {{2, 'C'}}},
        {2, {{3, 'G'}}},
        {3, {{4, 'C'}}},
        {4, {{5, 'T'}}},
        {5, {{6, 'G'}}}
    };
    auto res = getKmers(automaton, std::vector<State>{6}, std::vector<Length>{3});
    std::ranges::sort(res);

    std::vector<std::string> expected{
        "ACG",
        "CGC",
        "GCT",
        "CTG",
    };
    std::ranges::sort(expected);
    if (std::ranges::equal(expected, res)) {
        std::cout << "✅PASS\n";
    } else {
        std::cout << "❌FAIL\n";
    }
}

void test_single_diverge() {
    // ACT{GC}TG
    // ACTGTG
    // ---CTG
    std::cout << "------test_single_diverge------" << '\n';
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{1, 'A'}}          },
        {1, {{2, 'C'}}          },
        {2, {{3, 'T'}}          },
        {3, {{4, 'C'}, {5, 'G'}}},
        {4, {{6, 'T'}}          },
        {6, {{7, 'G'}}          },
        {5, {{8, 'T'}}          },
        {8, {{9, 'G'}}          }
    };
    auto res = getKmers(automaton, std::vector<State>{7, 9}, std::vector<Length>{3});
    std::ranges::sort(res);

    std::vector<std::string> expected{
        "ACT", "CTC", "TCT", "CTG", "CTG", "TGT", "GTG",
    };
    std::ranges::sort(expected);
    if (std::ranges::equal(expected, res)) {
        std::cout << "✅PASS\n";
    } else {
        std::cout << "❌FAIL\n";
    }
}
