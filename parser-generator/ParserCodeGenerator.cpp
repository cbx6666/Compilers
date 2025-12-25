#include "ParserCodeGenerator.h"
#include <algorithm>
#include <sstream>

using namespace std;

string ParserCodeGenerator::toValidIdentifier(const string &name) {
    string result = name;
    // 将单引号替换为下划线
    replace(result.begin(), result.end(), '\'', '_');
    return result;
}

string ParserCodeGenerator::generateParserCode(
    const Grammar &grammar,
    const map<string, map<string, ProductionRule>> &table) {
    ostringstream oss;

    // 生成头文件
    oss << "#include <vector>\n";
    oss << "#include <string>\n";
    oss << "#include <stdexcept>\n";
    oss << "\n";
    oss << "using namespace std;\n";
    oss << "\n";
    oss << "#ifndef TOKEN_DEFINED\n";
    oss << "#define TOKEN_DEFINED\n";
    oss << "struct Token {\n";
    oss << "    string type;\n";
    oss << "    string value;\n";
    oss << "    int line;\n";
    oss << "    int column;\n";
    oss << "    \n";
    oss << "    Token(string t, string v, int l, int c) : type(t), value(v), "
           "line(l), column(c) {}\n";
    oss << "    \n";
    oss << "    string toString() const {\n";
    oss << "        return \"Token(\" + type + \", \" + value + \", \" + "
           "to_string(line) + \", \" + to_string(column) + \")\";\n";
    oss << "    }\n";
    oss << "};\n";
    oss << "#endif\n";
    oss << "\n";

    // 生成 Parser 类
    oss << generateParserClass(grammar, table);

    return oss.str();
}

string ParserCodeGenerator::generateParserClass(
    const Grammar &grammar,
    const map<string, map<string, ProductionRule>> &table) {
    ostringstream oss;

    oss << "class Parser {\n";
    oss << "  private:\n";
    oss << "    vector<Token*> tokens;\n";
    oss << "    size_t currentPos;\n";
    oss << "    \n";
    oss << "    // 获取当前 token 的类型（如果已结束则返回 \"$\"）\n";
    oss << "    string currentTokenType() {\n";
    oss << "        if (currentPos >= tokens.size()) {\n";
    oss << "            return \"$\";\n";
    oss << "        }\n";
    oss << "        return tokens[currentPos]->type;\n";
    oss << "    }\n";
    oss << "    \n";
    oss << "    // 消耗当前 token（移动到下一个）\n";
    oss << "    void consume() {\n";
    oss << "        if (currentPos < tokens.size()) {\n";
    oss << "            currentPos++;\n";
    oss << "        }\n";
    oss << "    }\n";
    oss << "    \n";
    oss << "    // 抛出语法错误\n";
    oss << "    void error(const string& msg) {\n";
    oss << "        string tokenInfo = currentPos < tokens.size() ? \n";
    oss << "            tokens[currentPos]->toString() : \"EOF\";\n";
    oss << "        throw runtime_error(\"Parse error: \" + msg + \" at \" + "
           "tokenInfo);\n";
    oss << "    }\n";
    oss << "    \n";

    // 为每个非终结符生成解析方法声明
    for (const string &nonTerminal : grammar.nonTerminals) {
        oss << "    void parse" << toValidIdentifier(nonTerminal) << "();\n";
    }
    oss << "    \n";
    oss << "  public:\n";
    oss << "    Parser(const vector<Token*>& tokenList) : tokens(tokenList), "
           "currentPos(0) {}\n";
    oss << "    \n";
    oss << "    // 开始解析\n";
    oss << "    void parse() {\n";
    oss << "        parse" << toValidIdentifier(grammar.startSymbol) << "();\n";
    oss << "        if (currentTokenType() != \"$\") {\n";
    oss << "            error(\"Expected EOF\");\n";
    oss << "        }\n";
    oss << "    }\n";
    oss << "};\n";
    oss << "\n";

    // 生成解析方法的实现
    oss << generateParseMethods(grammar, table);

    return oss.str();
}

string ParserCodeGenerator::generateParseMethods(
    const Grammar &grammar,
    const map<string, map<string, ProductionRule>> &table) {
    ostringstream oss;

    // 为每个非终结符生成解析方法
    for (const string &nonTerminal : grammar.nonTerminals) {
        oss << "void Parser::parse" << toValidIdentifier(nonTerminal)
            << "() {\n";
        oss << "    string lookahead = currentTokenType();\n";
        oss << "    \n";

        // 查找预测分析表中的条目
        auto rowIt = table.find(nonTerminal);
        if (rowIt == table.end()) {
            oss << "    error(\"No production rule for " << nonTerminal
                << "\");\n";
            oss << "    return;\n";
            oss << "}\n\n";
            continue;
        }

        // 为每个可能的终结符生成分支
        bool hasCases = false;
        for (const auto &entry : rowIt->second) {
            const string &terminal = entry.first;
            const ProductionRule &rule = entry.second;

            // 查找对应的产生式
            for (const auto &prod : grammar.productions) {
                if (prod.left == rule.left &&
                    rule.candidateIndex < static_cast<int>(prod.right.size())) {
                    const vector<string> &candidate =
                        prod.right[rule.candidateIndex];

                    if (hasCases) {
                        oss << "    } else if (lookahead == \"" << terminal
                            << "\") {\n";
                    } else {
                        oss << "    if (lookahead == \"" << terminal
                            << "\") {\n";
                        hasCases = true;
                    }

                    // 生成产生式右侧的处理
                    bool firstSymbol = true;
                    for (const string &symbol : candidate) {
                        if (symbol == "ε") {
                            // 空产生式，什么都不做
                            continue;
                        } else if (grammar.nonTerminals.find(symbol) !=
                                   grammar.nonTerminals.end()) {
                            // 非终结符：递归调用解析方法（方法内部会处理 token
                            // 消耗）
                            oss << "        parse" << toValidIdentifier(symbol)
                                << "();\n";
                            // 更新 lookahead（非终结符方法可能消耗了 token）
                            oss << "        lookahead = currentTokenType();\n";
                            firstSymbol = false;
                        } else {
                            // 终结符处理
                            // 只有当是产生式第一个符号且等于预测表的终结符时，
                            // 才跳过 lookahead 检查（外层 if 已确认），直接消耗
                            // token 其他情况需要先检查 lookahead 再消耗 token
                            if (!firstSymbol || symbol != terminal) {
                                oss << "        if (lookahead != \"" << symbol
                                    << "\") {\n";
                                oss << "            error(\"Expected " << symbol
                                    << "\");\n";
                                oss << "        }\n";
                            }
                            oss << "        consume();\n";
                            // 更新 lookahead
                            oss << "        lookahead = currentTokenType();\n";
                            firstSymbol = false;
                        }
                    }
                    break;
                }
            }
        }

        if (hasCases) {
            oss << "    } else {\n";
            oss << "        error(\"Unexpected token for " << nonTerminal
                << ", expected one of: ";
            bool first = true;
            for (const auto &entry : rowIt->second) {
                if (!first)
                    oss << ", ";
                oss << entry.first;
                first = false;
            }
            oss << "\");\n";
            oss << "    }\n";
        } else {
            oss << "    error(\"No valid production for " << nonTerminal
                << "\");\n";
        }

        oss << "}\n\n";
    }

    return oss.str();
}
