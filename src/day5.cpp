#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utility.hpp"

// Adjacency-lists representation of a digraph.
using Graph = std::unordered_map<int, std::set<int>>;

Graph buildDependencyGraph(const std::vector<std::vector<int>>& rules)
{
    Graph g;
    for (const auto& rule : rules) {
        const auto u = rule.front();
        const auto v = rule.back();

        g[v].insert(u);
    }
    return g;
}

bool isUpdateCorrect(const Graph& dependencyGraph, const std::vector<int>& update)
{
    using namespace std;

    unordered_map<int, int> indexes;
    for (int i = 0; i < update.size(); ++i) {
        indexes[update[i]] = i;
    }

    for (int i = 0; i < update.size(); ++i) {
        const auto& depends = dependencyGraph.at(update[i]);
        for (const auto u : depends) {
            const auto vIt = indexes.find(u);
            if (vIt == indexes.cend()) {
                // This update doesn't contain the dependency node, it's OK.
                continue;
            }
            if (vIt->second > i) {
                // Dependency came *after* the current node, this update is NOT correct.
                return false;
            }
        }
    }

    return true;
}

std::vector<int> fixUpdate(Graph dependencyGraph, const std::vector<int>& update)
{
    using namespace std;

    unordered_set<int> numsSet(update.cbegin(), update.cend());

    for (auto it = dependencyGraph.begin(); it != dependencyGraph.end();) {
        if (!numsSet.count(it->first)) {
            it = dependencyGraph.erase(it);
        }
        else {
            auto& deps = it->second;
            for (auto depsIt = deps.begin(); depsIt != deps.end();) {
                if (!numsSet.count(*depsIt)) {
                    depsIt = deps.erase(depsIt);
                }
                else {
                    depsIt++;
                }
            }
            it++;
        }
    }

    auto fixedUpdate = update;
    for (int i = 0; i < update.size(); ++i) {
        fixedUpdate[dependencyGraph[update[i]].size()] = update[i];
    }
    return fixedUpdate;
}

void solveDay5()
{
    using namespace std;

    const auto lines = getInputLines("../input/day5.input");

    // Find the empty line
    const auto separatorIt = find(lines.cbegin(), lines.cend(), "");

    // Split rules and updates sections
    const vector<string> rulesInput(lines.cbegin(), separatorIt);
    const vector<string> updatesInput(separatorIt + 1, lines.cend());

    const auto rules = parseVectorInt(rulesInput, '|');
    const auto updates = parseVectorInt(updatesInput, ',');

    const auto g = buildDependencyGraph(rules);

    auto sum = 0;
    auto fixedSum = 0;

    for (const auto& update : updates) {
        if (isUpdateCorrect(g, update)) {
            sum += update[update.size() / 2];
        }
        else {
            const auto fixedUpdate = fixUpdate(g, update);
            fixedSum += fixedUpdate[fixedUpdate.size() / 2];
        }
    }

    cout << "Part 1: " << sum << endl;
    cout << "Part 2: " << fixedSum << endl;
}
