#pragma once
#include "GrammarParser.h"
#include <map>
#include <set>
#include <string>

using namespace std;

class FollowCalculator {
  public:
    // 计算所有非终结符的 FOLLOW 集合
    // 需要传入已经计算好的 FIRST 集合
    map<string, set<string>>
    calculateFollow(const Grammar &grammar,
                    const map<string, set<string>> &first);

  private:
    // 计算符号串的 FIRST 集合（用于 FOLLOW 计算）
    set<string> firstOfString(const vector<string> &symbols,
                              const map<string, set<string>> &first);
};
