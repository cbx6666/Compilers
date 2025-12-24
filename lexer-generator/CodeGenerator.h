#pragma once
#include "DFA.h"
#include "FileParser.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

// 代码生成器：将DFA转换为可执行的词法分析器代码
class CodeGenerator {
  public:
    // 生成词法分析器代码
    // rules: 词法规则列表
    // dfas: 每个规则对应的DFA
    string generateLexerCode(const vector<LexerRule> &rules,
                             const vector<shared_ptr<DFA>> &dfas);

  private:
    // 生成Token结构定义
    string generateTokenStruct();

    // 生成Lexer类定义
    string generateLexerClass(const vector<LexerRule> &rules,
                              const vector<shared_ptr<DFA>> &dfas);

    // 为每个DFA生成匹配方法
    string generateMatchMethod(int index, const LexerRule &rule,
                               shared_ptr<DFA> dfa);
};
