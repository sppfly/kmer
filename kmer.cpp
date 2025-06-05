#include "kmer.hpp"

void dfs(State current, const std::vector<State> &accepts, std::string path, unsigned long k,
         std::unordered_map<State, std::vector<Transition>> &automaton,
         std::vector<std::string> &res) {
    if (path.length() >= k) {
        res.push_back(path.substr(path.size() - k, k));
    }
    if (std::ranges::find(accepts, current) != accepts.end()) {
        return;
    }
    for (const auto &[to, label] : automaton.at(current)) {
        dfs(to, accepts, path + label, k, automaton, res);
    }
}

std::vector<std::string> getKmers(std::unordered_map<State, std::vector<Transition>>& automaton,
                                  const std::vector<State> &accepts, std::vector<Length> ks) {
    std::vector<std::string> res;

    dfs(0, accepts, "", ks.at(0), automaton, res);
    // RVO here I guess, but should I use string::view?
    return res;
}