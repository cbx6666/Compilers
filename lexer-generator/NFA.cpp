#include "NFA.h"
#include <queue>

using namespace std;

set<shared_ptr<NFAState>> NFA::epsilonClosure(const set<shared_ptr<NFAState>>& states) {
    set<shared_ptr<NFAState>> closure(states);
    queue<shared_ptr<NFAState>> workQueue;
    
    // 将所有初始状态加入队列
    for (auto state : states) {
        workQueue.push(state);
    }
    
    // 通过epsilon转换扩展闭包
    while (!workQueue.empty()) {
        auto state = workQueue.front();
        workQueue.pop();
        
        // 检查epsilon转换（'\0' 表示epsilon）
        if (state->transitions.find('\0') != state->transitions.end()) {
            for (auto nextState : state->transitions['\0']) {
                if (closure.find(nextState) == closure.end()) {
                    closure.insert(nextState);
                    workQueue.push(nextState);
                }
            }
        }
    }
    
    return closure;
}

set<shared_ptr<NFAState>> NFA::getAllStates() {
    set<shared_ptr<NFAState>> allStates;
    queue<shared_ptr<NFAState>> workQueue;
    
    workQueue.push(start);
    allStates.insert(start);
    
    while (!workQueue.empty()) {
        auto state = workQueue.front();
        workQueue.pop();
        
        for (auto& pair : state->transitions) {
            for (auto nextState : pair.second) {
                if (allStates.find(nextState) == allStates.end()) {
                    allStates.insert(nextState);
                    workQueue.push(nextState);
                }
            }
        }
    }
    
    return allStates;
}
