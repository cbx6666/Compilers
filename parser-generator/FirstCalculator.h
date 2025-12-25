#pragma once
#include "GrammarParser.h"
#include <map>
#include <set>
#include <string>

using namespace std;

class FirstCalculator {
  public:
    // 计算 FIRST 集合：
    // - 返回的 map 同时包含终结符和非终结符的 FIRST
    // - 空产生式用空向量表示，对应 FIRST(ε) = { ε }
    map<string, set<string>> calculateFirst(const Grammar &grammar);

  private:
    // 计算符号串 α 的 FIRST(α)，基于当前的 FIRST 映射
    set<string> firstOfSequence(const vector<string> &sequence,
                                const Grammar &grammar,
                                const map<string, set<string>> &firstMap);
};
