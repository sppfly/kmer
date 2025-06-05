#include "test.hpp"
#include <algorithm>
#include <iostream>

void test_simple() {
    // ACGCTG
    std::cout << "------test_simple------" << '\n';
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{.to=1, .label='A'}}},
        {1, {{.to=2, .label='C'}}},
        {2, {{.to=3, .label='G'}}},
        {3, {{.to=4, .label='C'}}},
        {4, {{.to=5, .label='T'}}},
        {5, {{.to=6, .label='G'}}}
    };
    auto res = getKmers(automaton, std::vector<State>{6}, std::vector<Length>{3});

    std::unordered_set<std::string> expected{
        "ACG",
        "CGC",
        "GCT",
        "CTG",
    };
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
        {0, {{.to=1, .label='A'}}          },
        {1, {{.to=2, .label='C'}}          },
        {2, {{.to=3, .label='T'}}          },
        {3, {{.to=4, .label='C'}, {.to=5, .label='G'}}},
        {4, {{.to=6, .label='T'}}          },
        {6, {{.to=7, .label='G'}}          },
        {5, {{.to=8, .label='T'}}          },
        {8, {{.to=9, .label='G'}}          }
    };
    auto res = getKmers(automaton, std::vector<State>{7, 9}, std::vector<Length>{3});

    std::unordered_set<std::string> expected{
        "ACT", "CTC", "TCT", "CTG", "CTG", "TGT", "GTG",
    };
    if (std::ranges::equal(expected, res)) {
        std::cout << "✅PASS\n";
    } else {
        std::cout << "❌FAIL\n";
    }
}
