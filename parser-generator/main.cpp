#include "FirstCalculator.h"
#include "FollowCalculator.h"
#include "GrammarParser.h"
#include "ParserCodeGenerator.h"
#include "ParsingTable.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    // 文件路径
    string grammarFile = "grammar_rules.txt";
    string lexerRulesFile = "../lexer-generator/lexer_rules.txt";
    string outputFile = "generated_parser.cpp";

    cout << "读取语法规则文件: " << grammarFile << endl;

    try {
        // 1. 解析语法规则文件
        GrammarParser grammarParser;
        Grammar grammar =
            grammarParser.parseGrammar(grammarFile, lexerRulesFile);
        cout << "读取到 " << grammar.productions.size() << " 个产生式" << endl;

        // 2. 计算 FIRST 集合
        cout << "计算 FIRST 集合..." << endl;
        FirstCalculator firstCalc;
        map<string, set<string>> first = firstCalc.calculateFirst(grammar);

        // 3. 计算 FOLLOW 集合
        cout << "计算 FOLLOW 集合..." << endl;
        FollowCalculator followCalc;
        map<string, set<string>> follow =
            followCalc.calculateFollow(grammar, first);

        // 4. 构建预测分析表
        cout << "构建预测分析表..." << endl;
        ParsingTable tableBuilder;
        map<string, map<string, ProductionRule>> table =
            tableBuilder.buildTable(grammar, first, follow);

        // 5. 生成解析器代码
        cout << "生成语法分析器代码..." << endl;
        ParserCodeGenerator codeGen;
        string parserCode = codeGen.generateParserCode(grammar, table);

        // 6. 写入文件
        cout << "写入文件: " << outputFile << endl;
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "错误：无法打开输出文件 " << outputFile << endl;
            return 1;
        }

        outFile << parserCode;
        outFile.close();

        cout << "语法分析器生成成功！" << endl;
        cout << "输出文件: " << outputFile << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
