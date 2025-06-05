#include "kmer.hpp"
#include <unordered_set>
#include <vector>

void dfs(State current, const std::vector<State> &accepts, std::string path, std::vector<Length> ks,
         std::unordered_map<State, std::vector<Transition>> &automaton,
         std::unordered_map<Length, std::unordered_set<std::string>> &res) {
    for (const auto &k : ks) {
        if (path.length() >= k) {
            res.at(k).insert(path.substr(path.size() - k, k));
        }
    }
    if (std::ranges::find(accepts, current) != accepts.end()) {
        return;
    }
    for (const auto &[to, label] : automaton.at(current)) {
        dfs(to, accepts, path + label, ks, automaton, res);
    }
}

auto getKmers(std::unordered_map<State, std::vector<Transition>> &automaton,
              const std::vector<State> &accepts, std::vector<Length> ks)
    -> std::unordered_map<Length, std::unordered_set<std::string>> {
    std::unordered_map<Length, std::unordered_set<std::string>> res{};
    for (const auto &k : ks) {
        res.insert({k, {}});
    }
    if (automaton.size() == 0) {
        return res;
    }
    dfs(0, accepts, "", ks, automaton, res);
    // RVO here I guess, but should I use string::view?
    return res;
}
