#include "FirstCalculator.h"
#include "FollowCalculator.h"
#include "GrammarParser.h"
#include "ParserCodeGenerator.h"
#include "ParserASTCodeGenerator.h"
#include "ParsingTable.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    string grammarFile = "grammar_rules.txt";
    string lexerRulesFile = "../lexer-generator/lexer_rules.txt";
    string outputPure = "generated_parser.cpp";
    string outputAST  = "generated_parser_ast.cpp";

    cout << "读取语法规则文件: " << grammarFile << endl;
    try {
        GrammarParser grammarParser;
        Grammar grammar = grammarParser.parseGrammar(grammarFile, lexerRulesFile);
        cout << "读取到 " << grammar.productions.size() << " 个产生式" << endl;

        cout << "计算 FIRST 集合..." << endl;
        FirstCalculator firstCalc;
        auto first = firstCalc.calculateFirst(grammar);

        cout << "计算 FOLLOW 集合..." << endl;
        FollowCalculator followCalc;
        auto follow = followCalc.calculateFollow(grammar, first);

        cout << "构建预测分析表..." << endl;
        ParsingTable tableBuilder;
        auto table = tableBuilder.buildTable(grammar, first, follow);

        // 生成纯语法检查版
        cout << "生成纯语法分析器代码..." << endl;
        ParserCodeGenerator pureGen;
        string pureCode = pureGen.generateParserCode(grammar, table);
        ofstream out1(outputPure);
        if (!out1.is_open()) { cerr << "无法写入 " << outputPure << endl; return 1; }
        out1 << pureCode; out1.close();
        cout << "写入文件: " << outputPure << endl;

        // 生成 AST 版
        cout << "生成 AST 版语法分析器代码..." << endl;
        ParserASTCodeGenerator astGen;
        string astCode = astGen.generateParserAST(grammar, table);
        ofstream out2(outputAST);
        if (!out2.is_open()) { cerr << "无法写入 " << outputAST << endl; return 1; }
        out2 << astCode; out2.close();
        cout << "写入文件: " << outputAST << endl;

        cout << "生成完成。" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}