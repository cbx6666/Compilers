#pragma once
#include "DFA.h"
#include <memory>
#include <set>
#include <vector>

using namespace std;

// DFA最小化算法：合并等价状态
class DFAMinimizer {
public:
    // 最小化DFA
    shared_ptr<DFA> minimize(shared_ptr<DFA> dfa);
    
private:
    // 收集DFA中所有可能的输入字符
    set<char> collectAlphabet(shared_ptr<DFA> dfa);
    
    // 细化划分：根据字符转换将划分进一步分割
    vector<set<shared_ptr<DFAState>>> refinePartition(
        const set<shared_ptr<DFAState>>& partition,
        const vector<set<shared_ptr<DFAState>>>& allPartitions,
        const set<char>& alphabet);
    
    // 构建最小化后的DFA
    shared_ptr<DFA> buildMinimizedDFA(
        shared_ptr<DFA> originalDFA,
        const vector<set<shared_ptr<DFAState>>>& partitions);
};
