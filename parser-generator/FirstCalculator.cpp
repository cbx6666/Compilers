#include "FirstCalculator.h"

using namespace std;

set<string> FirstCalculator::firstOfSequence(
    const vector<string> &sequence, const Grammar &grammar,
    const map<string, set<string>> &firstMap) {
    set<string> result;

    // α = ε
    if (sequence.empty()) {
        result.insert("ε");
        return result;
    }

    // FIRST(X1 X2 ... Xn)
    for (size_t i = 0; i < sequence.size(); i++) {
        const string &X = sequence[i];

        // 终结符：FIRST 直接是自身
        if (grammar.terminals.find(X) != grammar.terminals.end()) {
            result.insert(X);
            return result;
        }

        // 非终结符：从 firstMap 中取 FIRST(X)
        auto it = firstMap.find(X);
        // 加入 FIRST(X) - {ε}
        for (const string &t : it->second) {
            if (t != "ε") {
                result.insert(t);
            }
        }

        // 如果 FIRST(X) 不含 ε，则停止
        if (it->second.find("ε") == it->second.end()) {
            return result;
        }

        // 如果到最后一个符号都能推出 ε，则 ε ∈ FIRST(α)
        if (i == sequence.size() - 1) {
            result.insert("ε");
            return result;
        }
    }

    return result;
}

map<string, set<string>>
FirstCalculator::calculateFirst(const Grammar &grammar) {
    map<string, set<string>> first;

    // 初始化：终结符
    for (const string &t : grammar.terminals) {
        first[t].insert(t);
    }

    // 初始化：非终结符为空集合
    for (const string &A : grammar.nonTerminals) {
        (void)first[A]; // 确保 key 存在
    }

    // 迭代直到收敛
    bool changed = true;
    while (changed) {
        changed = false;

        for (const auto &prod : grammar.productions) {
            const string &A = prod.left;

            for (const auto &candidate : prod.right) {
                set<string> firstAlpha = firstOfSequence(candidate, grammar, first);

                size_t before = first[A].size();
                first[A].insert(firstAlpha.begin(), firstAlpha.end());
                if (first[A].size() != before) {
                    changed = true;
                }
            }
        }
    }

    return first;
}
