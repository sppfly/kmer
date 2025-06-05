#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using State = int;

struct Transition {
    // State current;
    State to;
    char  label;
};

void dfs(State current, State accept, std::string path, unsigned long k,
         std::unordered_map<State, std::vector<Transition>> &automaton) {
    if (path.length() >= k) {
        std::cout << path.substr(path.size() - k, k) << '\n';
    }
    if (current == accept) {
        return;
    }
    for (const auto &[to, label] : automaton.at(current)) {
        dfs(to, accept, path + label, k, automaton);
    }
}

int main() {
    // ACGCTG
    std::unordered_map<State, std::vector<Transition>> automaton{
        {0, {{1, 'A'}}},
        {1, {{2, 'C'}}},
        {2, {{3, 'G'}}},
        {3, {{4, 'C'}}},
        {4, {{5, 'T'}}},
        {5, {{6, 'G'}}}
    };
    dfs(0, 6, "", 3, automaton);
}
