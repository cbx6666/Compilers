#include "DFAMinimizer.h"
#include <stdexcept>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

shared_ptr<DFA> DFAMinimizer::minimize(shared_ptr<DFA> dfa) {
    if (!dfa || dfa->states.empty()) {
        return dfa;
    }
    
    // 收集字母表
    set<char> alphabet = collectAlphabet(dfa);
    
    // 初始划分：接受状态和非接受状态
    vector<set<shared_ptr<DFAState>>> partitions;
    set<shared_ptr<DFAState>> acceptingStates;
    set<shared_ptr<DFAState>> nonAcceptingStates;
    
    for (auto state : dfa->states) {
        if (state->isAccepting) {
            acceptingStates.insert(state);
        } else {
            nonAcceptingStates.insert(state);
        }
    }
    
    if (!acceptingStates.empty()) {
        partitions.push_back(acceptingStates);
    }
    if (!nonAcceptingStates.empty()) {
        partitions.push_back(nonAcceptingStates);
    }
    
    // 如果只有一个划分，不需要最小化
    if (partitions.size() <= 1) {
        return dfa;
    }
    
    // 不断细化划分直到不再变化
    bool changed = true;
    while (changed) {
        changed = false;
        vector<set<shared_ptr<DFAState>>> newPartitions;
        
        for (const auto& partition : partitions) {
            if (partition.size() == 1) {
                // 单个状态不需要细化
                newPartitions.push_back(partition);
                continue;
            }
            
            // 尝试细化这个划分
            vector<set<shared_ptr<DFAState>>> refined = refinePartition(partition, partitions, alphabet);
            if (refined.size() > 1) {
                changed = true;
                newPartitions.insert(newPartitions.end(), refined.begin(), refined.end());
            } else {
                newPartitions.push_back(partition);
            }
        }
        
        partitions = newPartitions;
    }
    
    // 构建最小化后的DFA
    return buildMinimizedDFA(dfa, partitions);
}

set<char> DFAMinimizer::collectAlphabet(shared_ptr<DFA> dfa) {
    set<char> alphabet;
    
    for (auto state : dfa->states) {
        for (auto& pair : state->transitions) {
            alphabet.insert(pair.first);
        }
    }
    
    return alphabet;
}

vector<set<shared_ptr<DFAState>>> DFAMinimizer::refinePartition(
    const set<shared_ptr<DFAState>>& partition,
    const vector<set<shared_ptr<DFAState>>>& allPartitions,
    const set<char>& alphabet) {
    
    // 为每个状态计算"签名"（根据转换到哪个划分）
    map<string, set<shared_ptr<DFAState>>> groups;
    
    for (auto state : partition) {
        // 构建状态的签名：对于每个字符，转换到哪个划分
        string signature;
        for (char c : alphabet) {
            if (state->hasTransition(c)) {
                auto targetState = state->transitions[c];
                // 找到targetState属于哪个划分
                int partitionIndex = -1;
                for (int i = 0; i < static_cast<int>(allPartitions.size()); i++) {
                    if (allPartitions[i].find(targetState) != allPartitions[i].end()) {
                        partitionIndex = i;
                        break;
                    }
                }
                signature += to_string(partitionIndex) + ",";
            } else {
                signature += "-1,";  // 没有转换
            }
        }
        
        groups[signature].insert(state);
    }
    
    // 将分组转换为vector
    vector<set<shared_ptr<DFAState>>> result;
    for (auto& pair : groups) {
        result.push_back(pair.second);
    }
    
    return result;
}

shared_ptr<DFA> DFAMinimizer::buildMinimizedDFA(
    shared_ptr<DFA> originalDFA,
    const vector<set<shared_ptr<DFAState>>>& partitions) {
    
    // 为每个划分创建新的DFA状态
    map<shared_ptr<DFAState>, shared_ptr<DFAState>> stateMap;  // 原状态 -> 新状态
    map<set<shared_ptr<DFAState>>, shared_ptr<DFAState>> partitionMap;  // 划分 -> 新状态
    
    int newStateId = 0;
    
    // 创建新状态
    for (const auto& partition : partitions) {
        // 选择代表状态（通常是第一个）
        shared_ptr<DFAState> representative = *partition.begin();
        auto newState = make_shared<DFAState>(newStateId++);
        newState->isAccepting = representative->isAccepting;
        
        partitionMap[partition] = newState;
        
        // 建立原状态到新状态的映射
        for (auto oldState : partition) {
            stateMap[oldState] = newState;
        }
    }
    
    // 构建转换
    for (const auto& partition : partitions) {
        auto newState = partitionMap[partition];
        auto representative = *partition.begin();
        
        // 复制代表状态的转换，但指向新的目标状态
        for (auto& pair : representative->transitions) {
            char c = pair.first;
            auto oldTarget = pair.second;
            auto newTarget = stateMap[oldTarget];
            newState->addTransition(c, newTarget);
        }
    }
    
    // 找到新的起始状态
    auto newStart = stateMap[originalDFA->start];
    
    // 创建新的DFA
    auto minimizedDFA = make_shared<DFA>(newStart);
    
    // 添加所有新状态
    for (const auto& pair : partitionMap) {
        minimizedDFA->addState(pair.second);
    }
    
    return minimizedDFA;
}
