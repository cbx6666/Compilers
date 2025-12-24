#include "SubsetConstruction.h"
#include <queue>
#include <stdexcept>

using namespace std;

shared_ptr<DFA> SubsetConstruction::convert(shared_ptr<NFA> nfa) {
    if (!nfa) {
        throw runtime_error("NFA为空");
    }

    // 收集所有输入字符（字母表）
    set<char> alphabet = collectAlphabet(nfa);

    // 创建DFA状态映射：NFA状态集合 -> DFA状态
    map<set<shared_ptr<NFAState>>, shared_ptr<DFAState>> stateMap;

    // 创建DFA状态ID计数器
    int dfaStateId = 0;

    // 初始DFA状态：NFA起始状态的epsilon闭包
    set<shared_ptr<NFAState>> initialNfaStates;
    initialNfaStates.insert(nfa->start);
    set<shared_ptr<NFAState>> initialClosure =
        nfa->epsilonClosure(initialNfaStates);

    // 创建初始DFA状态
    auto initialDfaState = make_shared<DFAState>(dfaStateId++);
    initialDfaState->nfaStates = initialClosure;
    stateMap[initialClosure] = initialDfaState;

    // 创建DFA
    auto dfa = make_shared<DFA>(initialDfaState);

    // 未处理的DFA状态队列
    queue<shared_ptr<DFAState>> unprocessed;
    unprocessed.push(initialDfaState);

    // 处理所有未处理的DFA状态
    while (!unprocessed.empty()) {
        auto currentDfaState = unprocessed.front();
        unprocessed.pop();

        // 检查是否为接受状态：如果包含的NFA状态中有接受状态，则该DFA状态为接受状态
        for (auto nfaState : currentDfaState->nfaStates) {
            if (nfaState->isAccepting) {
                currentDfaState->isAccepting = true;
                break;
            }
        }

        // 对每个输入字符计算转换
        for (char c : alphabet) {
            // 计算move操作
            set<shared_ptr<NFAState>> moveResult =
                move(currentDfaState->nfaStates, c);

            if (!moveResult.empty()) {
                // 计算epsilon闭包
                set<shared_ptr<NFAState>> closure =
                    nfa->epsilonClosure(moveResult);

                // 检查这个NFA状态集合是否已经有对应的DFA状态
                shared_ptr<DFAState> targetDfaState;
                if (stateMap.find(closure) != stateMap.end()) {
                    // 已存在，使用已有的DFA状态
                    targetDfaState = stateMap[closure];
                } else {
                    // 不存在，创建新的DFA状态
                    targetDfaState = make_shared<DFAState>(dfaStateId++);
                    targetDfaState->nfaStates = closure;
                    stateMap[closure] = targetDfaState;
                    dfa->addState(targetDfaState);
                    unprocessed.push(targetDfaState);
                }

                // 添加转换
                currentDfaState->addTransition(c, targetDfaState);
            }
        }
    }

    return dfa;
}

set<shared_ptr<NFAState>>
SubsetConstruction::move(const set<shared_ptr<NFAState>> &states, char c) {
    set<shared_ptr<NFAState>> result;

    // 从状态集合中的每个状态，通过字符c能到达的状态
    for (auto state : states) {
        if (state->transitions.find(c) != state->transitions.end()) {
            for (auto nextState : state->transitions[c]) {
                result.insert(nextState);
            }
        }
    }

    return result;
}

set<char> SubsetConstruction::collectAlphabet(shared_ptr<NFA> nfa) {
    set<char> alphabet;

    // 获取所有NFA状态
    set<shared_ptr<NFAState>> allStates = nfa->getAllStates();

    // 收集所有转换中的字符（排除epsilon）
    for (auto state : allStates) {
        for (auto &pair : state->transitions) {
            char ch = pair.first;
            if (ch != '\0') { // 排除epsilon
                alphabet.insert(ch);
            }
        }
    }

    return alphabet;
}
