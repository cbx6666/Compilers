#pragma once
#include "GrammarParser.h"
#include "ParsingTable.h"
#include <string>

class ParserASTCodeGenerator {
public:
    // 生成“构建 AST 的递归下降解析器”源码字符串
    std::string generateParserAST(
        const Grammar& grammar,
        const std::map<std::string, std::map<std::string, ProductionRule>>& table);
};