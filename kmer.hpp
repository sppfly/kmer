#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using State = int;
using Length = unsigned long;

struct Transition {
    State to;
    char label;
};

void dfs(State current, const std::vector<State> &accepts, std::string path, unsigned long k,
         std::unordered_map<State, std::vector<Transition>> &automaton,
         std::unordered_map<Length, std::unordered_set<std::string>>);

auto getKmers(std::unordered_map<State, std::vector<Transition>> &automaton,
              const std::vector<State> &accepts, std::vector<Length> ks)
    -> std::unordered_map<Length, std::unordered_set<std::string>>;
