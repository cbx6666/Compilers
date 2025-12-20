#include "NFA.h"
#include <stack>

using namespace std;

set<shared_ptr<NFAState>> NFA::epsilonClosure(const set<shared_ptr<NFAState>>& states) {
    set<shared_ptr<NFAState>> closure(states);
    stack<shared_ptr<NFAState>> stack;
    
    // 将所有初始状态加入栈
    for (auto state : states) {
        stack.push(state);
    }
    
    // 通过epsilon转换扩展闭包
    while (!stack.empty()) {
        auto state = stack.top();
        stack.pop();
        
        // 检查epsilon转换（'\0' 表示epsilon）
        if (state->transitions.find('\0') != state->transitions.end()) {
            for (auto nextState : state->transitions['\0']) {
                if (closure.find(nextState) == closure.end()) {
                    closure.insert(nextState);
                    stack.push(nextState);
                }
            }
        }
    }
    
    return closure;
}

set<shared_ptr<NFAState>> NFA::getAllStates() {
    set<shared_ptr<NFAState>> allStates;
    stack<shared_ptr<NFAState>> stack;
    
    stack.push(start);
    allStates.insert(start);
    
    while (!stack.empty()) {
        auto state = stack.top();
        stack.pop();
        
        for (auto& pair : state->transitions) {
            for (auto nextState : pair.second) {
                if (allStates.find(nextState) == allStates.end()) {
                    allStates.insert(nextState);
                    stack.push(nextState);
                }
            }
        }
    }
    
    return allStates;
}
