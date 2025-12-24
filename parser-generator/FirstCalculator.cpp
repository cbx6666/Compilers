#include "FirstCalculator.h"

using namespace std;

set<string>
FirstCalculator::firstOfSymbol(const string &symbol, const Grammar &grammar,
                               map<string, set<string>> &firstCache) {
    // 如果已经计算过，直接返回
    if (firstCache.find(symbol) != firstCache.end()) {
        return firstCache[symbol];
    }

    set<string> first;

    // 如果是终结符，FIRST(a) = {a}
    if (grammar.terminals.find(symbol) != grammar.terminals.end()) {
        first.insert(symbol);
        firstCache[symbol] = first;
        return first;
    }

    // 如果是非终结符，需要查找所有产生式
    for (const auto &prod : grammar.productions) {
        if (prod.left == symbol) {
            // 对每个候选式计算 FIRST
            for (const auto &candidate : prod.right) {
                if (candidate.empty()) {
                    // 空产生式：ε ∈ FIRST(A)
                    first.insert("ε");
                } else {
                    // 计算符号串的 FIRST
                    set<string> candidateFirst =
                        firstOfString(candidate, grammar, firstCache);
                    first.insert(candidateFirst.begin(), candidateFirst.end());
                }
            }
        }
    }

    firstCache[symbol] = first;
    return first;
}

set<string>
FirstCalculator::firstOfString(const vector<string> &symbols,
                               const Grammar &grammar,
                               map<string, set<string>> &firstCache) {
    set<string> first;

    if (symbols.empty()) {
        first.insert("ε");
        return first;
    }

    // 对每个符号计算 FIRST
    for (size_t i = 0; i < symbols.size(); i++) {
        set<string> symbolFirst =
            firstOfSymbol(symbols[i], grammar, firstCache);

        // 添加 FIRST(Xi) - {ε} 到结果
        for (const string &terminal : symbolFirst) {
            if (terminal != "ε") {
                first.insert(terminal);
            }
        }

        // 如果 ε 不在 FIRST(Xi) 中，停止
        if (symbolFirst.find("ε") == symbolFirst.end()) {
            break;
        }

        // 如果所有符号都能推导出 ε，则 ε ∈ FIRST(α)
        if (i == symbols.size() - 1) {
            first.insert("ε");
        }
    }

    return first;
}

map<string, set<string>>
FirstCalculator::calculateFirst(const Grammar &grammar) {
    // 缓存已经计算过的 FIRST 集合
    map<string, set<string>> firstCache;

    // 计算所有符号的 FIRST 集合
    // 先计算终结符
    for (const string &terminal : grammar.terminals) {
        set<string> first;
        first.insert(terminal);
        firstCache[terminal] = first;
    }

    // 计算所有非终结符的 FIRST 集合（可能需要多轮迭代）
    bool changed = true;
    while (changed) {
        changed = false;
        for (const string &nonTerminal : grammar.nonTerminals) {
            set<string> oldFirst = firstCache[nonTerminal];
            set<string> newFirst =
                firstOfSymbol(nonTerminal, grammar, firstCache);
            if (oldFirst != newFirst) {
                changed = true;
                firstCache[nonTerminal] = newFirst;
            }
        }
    }

    return firstCache;
}
