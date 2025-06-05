#include "kmer.hpp"
#include <iostream>
#include <print>
#include <random>
#include <unordered_map>

void test_branching_paths() {
    std::cout << "------test_branching_paths------" << '\n';
    // Accepting: 4, 5
    // Structure:  A → C → G -> G
    //                 ↘ T
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{.to = 1, .label = 'A'}}                         },
        {1, {{.to = 2, .label = 'C'}}                         },
        {2, {{.to = 3, .label = 'G'}, {.to = 4, .label = 'T'}}},
        {3, {{.to = 5, .label = 'G'}}                         }
    };
    auto res = getKmers(automaton, {4, 5}, {2, 3});
    std::unordered_map<Length, std::unordered_set<std::string>> expected{
        {2, {"AC", "CG", "CT", "GG"}},
        {3, {"ACG", "CGG", "ACT"}   }
    };
    bool ok = expected.size() == res.size();
    for (const auto &[k, s] : expected) {
        ok &= res.contains(k) && res.at(k) == s;
    }
    std::cout << (ok ? "✅PASS\n" : "❌FAIL\n");
}

void test_disconnected_states() {
    std::cout << "------test_disconnected_states------" << '\n';
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{.to = 1, .label = 'A'}}},
        {2, {{.to = 3, .label = 'C'}}}, // Disconnected
    };
    auto res = getKmers(automaton, {1}, {1});
    std::unordered_set<std::string> expected = {"A"};
    bool ok = res.at(1) == expected;
    std::cout << (ok ? "✅PASS\n" : "❌FAIL\n");
}

void test_empty_automaton() {
    std::cout << "------test_empty_automaton------" << '\n';
    std::unordered_map<State, std::vector<Transition>> automaton{};
    auto res = getKmers(automaton, {}, {1});
    bool ok = res.at(1).empty();
    std::cout << (ok ? "✅PASS\n" : "❌FAIL\n");
}

void test_long_sequence() {

    std::cout << "------test_long_sequence------" << '\n';

    constexpr int length = 1000;
    constexpr int k = 20;

    // Generate a high-entropy pseudo-random sequence from ACGT
    std::vector<char> bases = {'A', 'C', 'G', 'T'};
    std::string sequence;
    for (int i = 0; i < length; ++i) {
        sequence +=
            bases[(i * 7) % 4]; // 7 mod 4 = 3 (coprime with 4), ensures pattern won't repeat early
    }

    // Build automaton from the string
    std::unordered_map<State, std::vector<Transition>> automaton;
    for (int i = 0; i < length; ++i) {
        automaton[i] = {
            {.to = i + 1, .label = sequence[i]}
        };
    }

    auto res = getKmers(automaton, {length}, {k});
    const auto &actual = res.at(k);

    // Build expected output
    std::unordered_set<std::string> expected;
    for (int i = 0; i <= length - k; ++i) {
        expected.insert(sequence.substr(i, k));
    }

    bool ok = actual == expected;
    std::cout << (ok ? "✅PASS\n" : "❌FAIL\n");
    if (!ok) {
        std::cout << "Expected: " << expected.size() << " k-mers\n";
        std::cout << "Actual:   " << actual.size() << " k-mers\n";
    }
}

void test_long_random_sequence() {
    std::cout << "------test_long_random_sequence------" << '\n';

    constexpr int length = 1000;
    constexpr int k = 20;

    std::vector<char> bases = {'A', 'C', 'G', 'T'};
    std::string sequence;
    sequence.reserve(length);

    // Random number generation setup
    std::mt19937 rng(42); // fixed seed for reproducibility
    std::uniform_int_distribution<int> dist(0, 3);

    // Generate random DNA sequence
    for (int i = 0; i < length; ++i) {
        sequence += bases[dist(rng)];
    }

    // Build automaton from random sequence
    std::unordered_map<State, std::vector<Transition>> automaton;
    for (int i = 0; i < length; ++i) {
        automaton[i] = {
            {.to = i + 1, .label = sequence[i]}
        };
    }

    auto res = getKmers(automaton, {length}, {k});
    const auto &actual = res.at(k);

    // Expected: all sliding k-mers from the sequence
    std::unordered_set<std::string> expected;
    for (int i = 0; i <= length - k; ++i) {
        expected.insert(sequence.substr(i, k));
    }

    bool ok = actual == expected;
    std::cout << (ok ? "✅PASS\n" : "❌FAIL\n");
    if (!ok) {
        std::cout << "Expected: " << expected.size() << " k-mers\n";
        std::cout << "Actual:   " << actual.size() << " k-mers\n";

        // Optional: show first 5 mismatches
        std::vector<std::string> diff;
        for (const auto &s : expected) {
            if (!actual.contains(s)) {
                diff.push_back(s);
                if (diff.size() >= 5)
                    break;
            }
        }
        if (!diff.empty()) {
            std::cout << "Missing example k-mers:\n";
            for (const auto &s : diff)
                std::cout << s << '\n';
        }
    }
}