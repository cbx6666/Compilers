#pragma once
#include <map>
#include <set>
#include <memory>
#include <string>
#include "NFA.h"

using namespace std;

// DFA状态
class DFAState {
public:
    int id;
    map<char, shared_ptr<DFAState>> transitions;  // 转换表：字符 -> 目标状态（确定性的，每个字符只有一个目标状态）
    bool isAccepting;  // 是否为接受状态
    
    // 该DFA状态对应的NFA状态集合（子集构造时使用）
    set<shared_ptr<NFAState>> nfaStates;
    
    DFAState(int stateId) : id(stateId), isAccepting(false) {}
    
    // 添加转换边
    void addTransition(char ch, shared_ptr<DFAState> target) {
        transitions[ch] = target;
    }
    
    // 检查是否有某个字符的转换
    bool hasTransition(char ch) const {
        return transitions.find(ch) != transitions.end();
    }
};

// 确定有限自动机
class DFA {
public:
    shared_ptr<DFAState> start;   // 起始状态
    set<shared_ptr<DFAState>> states;  // 所有状态的集合
    
    DFA(shared_ptr<DFAState> s) : start(s) {
        states.insert(s);
    }
    
    // 添加状态
    void addState(shared_ptr<DFAState> state) {
        states.insert(state);
    }
    
    // 匹配字符串
    bool match(const string& input) {
        auto current = start;
        for (char ch : input) {
            if (!current->hasTransition(ch)) {
                return false;
            }
            current = current->transitions[ch];
        }
        return current->isAccepting;
    }
};
