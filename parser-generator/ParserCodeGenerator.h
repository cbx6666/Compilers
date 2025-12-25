#pragma once
#include "GrammarParser.h"
#include "ParsingTable.h"
#include <string>

using namespace std;

class ParserCodeGenerator {
  public:
    // 生成语法分析器代码
    // grammar: 文法
    // table: 预测分析表
    string
    generateParserCode(const Grammar &grammar,
                       const map<string, map<string, ProductionRule>> &table);

  private:
    // 将非终结符名称转换为有效的 C++ 标识符（替换单引号为下划线）
    string toValidIdentifier(const string &name);

    // 生成 Parser 类定义
    string
    generateParserClass(const Grammar &grammar,
                        const map<string, map<string, ProductionRule>> &table);

    // 生成解析方法的实现
    string
    generateParseMethods(const Grammar &grammar,
                         const map<string, map<string, ProductionRule>> &table);
};
