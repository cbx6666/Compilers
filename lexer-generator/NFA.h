#pragma once
#include <map>
#include <memory>
#include <set>
#include <vector>

using namespace std;

// NFA状态
class NFAState {
  public:
    int id;
    map<char, vector<shared_ptr<NFAState>>>
        transitions;  // 转换表：字符 -> 目标状态列表
    bool isAccepting; // 是否为终态

    NFAState(int stateId) : id(stateId), isAccepting(false) {}

    // 添加转换边
    void addTransition(char ch, shared_ptr<NFAState> target) {
        this->transitions[ch].push_back(target);
    }

    // 添加epsilon转换（用 '\0' 表示epsilon）
    void addEpsilonTransition(shared_ptr<NFAState> target) {
        this->transitions['\0'].push_back(target);
    }
};

// 非确定有限自动机
class NFA {
  public:
    shared_ptr<NFAState> start;  // 起始状态
    shared_ptr<NFAState> accept; // 接受状态

    NFA(shared_ptr<NFAState> s, shared_ptr<NFAState> a) : start(s), accept(a) {
        accept->isAccepting = true;
    }

    // 计算epsilon闭包
    set<shared_ptr<NFAState>>
    epsilonClosure(const set<shared_ptr<NFAState>> &states);

    // 获取所有状态
    set<shared_ptr<NFAState>> getAllStates();
};
