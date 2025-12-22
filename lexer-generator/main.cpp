#include "CodeGenerator.h"
#include "DFAMinimizer.h"
#include "FileParser.h"
#include "RegexParser.h"
#include "SubsetConstruction.h"
#include "Thompson.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
  // 直接指定文件路径
  string rulesFile = "lexer_rules.txt";
  string outputFile = "generated_lexer.cpp";

  try {
    // 1. 读取规则文件
    cout << "读取规则文件: " << rulesFile << endl;
    FileParser fileParser;
    vector<LexerRule> rules = fileParser.readLexerRules(rulesFile);
    cout << "读取到 " << rules.size() << " 条规则" << endl;

    // 2. 为每个规则构建DFA
    cout << "构建DFA..." << endl;
    RegexParser regexParser;
    ThompsonConstruction thompson;
    SubsetConstruction subset;
    DFAMinimizer minimizer;

    vector<shared_ptr<DFA>> dfas;

    for (size_t i = 0; i < rules.size(); i++) {
      const auto &rule = rules[i];
      cout << "  处理规则 [" << (i + 1) << "/" << rules.size()
           << "]: " << rule.tokenType << " -> " << rule.regex << endl;

      // 解析正则表达式
      auto ast = regexParser.parse(rule.regex);

      // Thompson构造：AST -> NFA
      auto nfa = thompson.build(ast);

      // 子集构造：NFA -> DFA
      auto dfa = subset.convert(nfa);

      // DFA最小化
      auto minimizedDFA = minimizer.minimize(dfa);

      dfas.push_back(minimizedDFA);

      cout << "    完成（状态数: " << minimizedDFA->states.size() << "）"
           << endl;
    }

    // 3. 生成词法分析器代码
    cout << "生成词法分析器代码..." << endl;
    CodeGenerator codeGenerator;
    string code = codeGenerator.generateLexerCode(rules, dfas);

    // 4. 写入文件
    cout << "写入文件: " << outputFile << endl;
    ofstream out(outputFile);
    if (!out.is_open()) {
      cerr << "错误：无法打开输出文件 " << outputFile << endl;
      return 1;
    }

    out << code;
    out.close();

    cout << "词法分析器生成成功！" << endl;
    cout << "输出文件: " << outputFile << endl;

  } catch (const exception &e) {
    cerr << "错误: " << e.what() << endl;
    return 1;
  }

  return 0;
}
