#pragma once
#include "GrammarParser.h"
#include <map>
#include <set>
#include <string>

using namespace std;

class FirstCalculator {
  public:
    // 计算所有符号的 FIRST 集合
    map<string, set<string>> calculateFirst(const Grammar &grammar);

  private:
    // 计算单个符号的 FIRST 集合
    set<string> firstOfSymbol(const string &symbol, const Grammar &grammar,
                              map<string, set<string>> &firstCache);

    // 计算符号串的 FIRST 集合
    set<string> firstOfString(const vector<string> &symbols,
                              const Grammar &grammar,
                              map<string, set<string>> &firstCache);
};
