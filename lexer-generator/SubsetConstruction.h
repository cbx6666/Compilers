#pragma once
#include "NFA.h"
#include "DFA.h"
#include <memory>
#include <set>

using namespace std;

// 子集构造算法：将NFA转换为DFA
class SubsetConstruction {
public:
    // 将NFA转换为DFA
    shared_ptr<DFA> convert(shared_ptr<NFA> nfa);
    
private:
    // 计算move操作：从状态集合通过字符c能到达的状态
    set<shared_ptr<NFAState>> move(const set<shared_ptr<NFAState>>& states, char c);
    
    // 收集NFA中所有可能的输入字符（排除epsilon）
    set<char> collectAlphabet(shared_ptr<NFA> nfa);
};
