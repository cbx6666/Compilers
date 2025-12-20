#include "NFA.h"
#include <stack>

using namespace std;

set<shared_ptr<NFAState>> NFA::epsilonClosure(const set<shared_ptr<NFAState>>& states) {
    set<shared_ptr<NFAState>> closure(states);
    stack<shared_ptr<NFAState>> workStack;
    
    // 将所有初始状态加入栈
    for (auto state : states) {
        workStack.push(state);
    }
    
    // 通过epsilon转换扩展闭包
    while (!workStack.empty()) {
        auto state = workStack.top();
        workStack.pop();
        
        // 检查epsilon转换（'\0' 表示epsilon）
        if (state->transitions.find('\0') != state->transitions.end()) {
            for (auto nextState : state->transitions['\0']) {
                if (closure.find(nextState) == closure.end()) {
                    closure.insert(nextState);
                    workStack.push(nextState);
                }
            }
        }
    }
    
    return closure;
}

set<shared_ptr<NFAState>> NFA::getAllStates() {
    set<shared_ptr<NFAState>> allStates;
    stack<shared_ptr<NFAState>> workStack;
    
    workStack.push(start);
    allStates.insert(start);
    
    while (!workStack.empty()) {
        auto state = workStack.top();
        workStack.pop();
        
        for (auto& pair : state->transitions) {
            for (auto nextState : pair.second) {
                if (allStates.find(nextState) == allStates.end()) {
                    allStates.insert(nextState);
                    workStack.push(nextState);
                }
            }
        }
    }
    
    return allStates;
}
