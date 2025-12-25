#include "FollowCalculator.h"

using namespace std;

set<string>
FollowCalculator::firstOfString(const vector<string> &symbols,
                                const map<string, set<string>> &first) {
    set<string> result;

    if (symbols.empty()) {
        result.insert("ε");
        return result;
    }

    // 对每个符号计算 FIRST
    for (size_t i = 0; i < symbols.size(); i++) {
        auto it = first.find(symbols[i]);
        if (it == first.end()) {
            // 如果符号不在 FIRST 映射中，停止
            break;
        }

        // 添加 FIRST(Xi) - {ε} 到结果
        for (const string &terminal : it->second) {
            if (terminal != "ε") {
                result.insert(terminal);
            }
        }

        // 如果 ε 不在 FIRST(Xi) 中，停止
        if (it->second.find("ε") == it->second.end()) {
            break;
        }

        // 如果所有符号都能推导出 ε，则 ε ∈ FIRST(α)
        if (i == symbols.size() - 1) {
            result.insert("ε");
        }
    }

    return result;
}

map<string, set<string>>
FollowCalculator::calculateFollow(const Grammar &grammar,
                                  const map<string, set<string>> &first) {
    map<string, set<string>> follow;

    // 初始化：$ ∈ FOLLOW(开始符号)
    if (!grammar.startSymbol.empty()) {
        follow[grammar.startSymbol].insert("$");
    }

    // 多轮迭代直到不再变化
    bool changed = true;
    while (changed) {
        changed = false;

        for (const auto &prod : grammar.productions) {
            const string &A = prod.left;

            for (const auto &candidate : prod.right) {
                if (candidate.empty())
                    continue;

                // 对于产生式 A -> αBβ，遍历每个符号 B
                for (size_t i = 0; i < candidate.size(); i++) {
                    const string &B = candidate[i];

                    // 只处理非终结符
                    if (grammar.nonTerminals.find(B) ==
                        grammar.nonTerminals.end())
                        continue;

                    // 计算 β = candidate[i+1...]
                    vector<string> beta(candidate.begin() + i + 1,
                                        candidate.end());

                    if (beta.empty()) {
                        // A -> αB，则 FOLLOW(A) ⊆ FOLLOW(B)
                        set<string> oldFollow = follow[B];
                        follow[B].insert(follow[A].begin(), follow[A].end());
                        if (oldFollow != follow[B]) {
                            changed = true;
                        }
                    } else {
                        // 计算 FIRST(β)
                        set<string> firstBeta = firstOfString(beta, first);

                        // FIRST(β) - {ε} ⊆ FOLLOW(B)
                        set<string> oldFollow = follow[B];
                        for (const string &terminal : firstBeta) {
                            if (terminal != "ε") {
                                follow[B].insert(terminal);
                            }
                        }

                        // 如果 ε ∈ FIRST(β)，则 FOLLOW(A) ⊆ FOLLOW(B)
                        if (firstBeta.find("ε") != firstBeta.end()) {
                            follow[B].insert(follow[A].begin(),
                                             follow[A].end());
                        }

                        if (oldFollow != follow[B]) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }

    return follow;
}
