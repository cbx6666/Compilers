#pragma once
#include <set>
#include <string>
#include <vector>

using namespace std;

// 产生式：一个非终结符的多个候选式
struct Production {
    string left; // 非终结符（左侧）
    vector<vector<string>>
        right; // 产生式体（多个候选式，每个候选式是符号序列）

    Production(const string &l) : left(l) {}
};

// 文法
struct Grammar {
    string startSymbol;             // 开始符号
    set<string> terminals;          // 终结符集合
    set<string> nonTerminals;       // 非终结符集合
    vector<Production> productions; // 产生式列表
};

class GrammarParser {
  public:
    Grammar parseGrammar(
        const string &filename,
        const string &lexerRulesFile = "../lexer-generator/lexer_rules.txt");

  private:
    set<string> loadTerminals(const string &lexerRulesFile);
    void parseProduction(const string &line, Grammar &grammar,
                         Production *&currentProduction,
                         set<string> &allSymbols);
};
