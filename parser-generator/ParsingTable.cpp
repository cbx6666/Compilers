#include "ParsingTable.h"
#include <iostream>

using namespace std;

static const vector<string> *
findCandidate(const Grammar &grammar, const ProductionRule &rule) {
    for (const auto &prod : grammar.productions) {
        if (prod.left == rule.left &&
            rule.candidateIndex >= 0 &&
            rule.candidateIndex < static_cast<int>(prod.right.size())) {
            return &prod.right[rule.candidateIndex];
        }
    }
    return nullptr;
}

bool ParsingTable::isEpsilonCandidate(const Grammar &grammar,
                                      const ProductionRule &rule) {
    const vector<string> *cand = findCandidate(grammar, rule);
    if (!cand)
        return false;
    // GrammarParser 用空 vector 表示 ε
    return cand->empty();
}

bool ParsingTable::tryPut(map<string, map<string, ProductionRule>> &table,
                          const Grammar &grammar, const string &A,
                          const string &terminal,
                          const ProductionRule &newRule) {
    auto &row = table[A];
    auto it = row.find(terminal);
    if (it == row.end()) {
        row[terminal] = newRule;
        return true;
    }

    const ProductionRule &oldRule = it->second;
    bool oldIsEps = isEpsilonCandidate(grammar, oldRule);
    bool newIsEps = isEpsilonCandidate(grammar, newRule);

    // 冲突策略：
    // - 如果是 ε vs 非 ε：优先非 ε（解决 ElsePart/ELSE 这类 dangling else 冲突）
    // - 否则：保留旧规则并报错（表示文法不是 LL(1)）
    if (oldIsEps && !newIsEps) {
        row[terminal] = newRule;
        return true;
    }
    if (!oldIsEps && newIsEps) {
        return false;
    }

    cerr << "  Unresolved: keep existing production (grammar not LL(1))"
         << endl;
    return false;
}

set<string>
ParsingTable::firstOfCandidate(const vector<string> &candidate,
                               const map<string, set<string>> &first) {
    set<string> result;

    if (candidate.empty()) {
        result.insert("ε");
        return result;
    }

    // 对每个符号计算 FIRST
    for (size_t i = 0; i < candidate.size(); i++) {
        auto it = first.find(candidate[i]);
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
        if (i == candidate.size() - 1) {
            result.insert("ε");
        }
    }

    return result;
}

map<string, map<string, ProductionRule>>
ParsingTable::buildTable(const Grammar &grammar,
                         const map<string, set<string>> &first,
                         const map<string, set<string>> &follow) {
    map<string, map<string, ProductionRule>> table;

    // 遍历所有产生式 A -> α
    for (const auto &prod : grammar.productions) {
        const string &A = prod.left; 

        // 遍历每个候选式 α
        for (size_t i = 0; i < prod.right.size(); i++) {
            const vector<string> &candidate = prod.right[i]; 
            ProductionRule rule(A, static_cast<int>(i));

            set<string> firstAlpha = firstOfCandidate(candidate, first);

            // 规则1：对每个 a ∈ FIRST(α)，将 A -> α 填入 M[A, a]
            for (const string &terminal : firstAlpha) {
                if (terminal != "ε") {
                    (void)tryPut(table, grammar, A, terminal, rule);
                }
            }

            // 规则2：如果 ε ∈ FIRST(α)，对每个 b ∈ FOLLOW(A)，将 A -> α 填入
            if (firstAlpha.find("ε") != firstAlpha.end()) {
                auto followIt = follow.find(A);
                if (followIt != follow.end()) {
                    for (const string &terminal : followIt->second) {
                        (void)tryPut(table, grammar, A, terminal, rule);
                    }
                }
            }
        }
    }

    return table;
}
