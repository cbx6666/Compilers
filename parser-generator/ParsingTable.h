#pragma once
#include "FirstCalculator.h"
#include "FollowCalculator.h"
#include "GrammarParser.h"
#include <map>
#include <set>
#include <string>
#include <vector>


using namespace std;

// 产生式规则：用索引表示 Production 中的某个候选式
struct ProductionRule {
    string left;        // 非终结符
    int candidateIndex; // 候选式在 Production.right 中的索引

    ProductionRule(const string &l, int idx) : left(l), candidateIndex(idx) {}

    bool operator<(const ProductionRule &other) const {
        if (left != other.left)
            return left < other.left;
        return candidateIndex < other.candidateIndex;
    }
};

class ParsingTable {
  public:
    // 构建预测分析表
    // 返回：表（map<非终结符, map<终结符, 产生式规则>>）
    map<string, map<string, ProductionRule>>
    buildTable(const Grammar &grammar, const map<string, set<string>> &first,
               const map<string, set<string>> &follow);

  private:
    // 计算产生式候选式的 FIRST 集合
    set<string> firstOfCandidate(const vector<string> &candidate,
                                 const map<string, set<string>> &first);
};
