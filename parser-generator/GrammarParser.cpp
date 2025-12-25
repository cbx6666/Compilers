#include "GrammarParser.h"
#include "../lexer-generator/FileParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

static string trim(const string &str) {
    const char *trim_chars = " \t\n";
    size_t start = str.find_first_not_of(trim_chars);
    if (start == string::npos)
        return "";
    size_t end = str.find_last_not_of(trim_chars);
    return str.substr(start, end - start + 1);
}

set<string> GrammarParser::loadTerminals(const string &lexerRulesFile) {
    set<string> terminals;
    FileParser fileParser;
    vector<LexerRule> rules = fileParser.readLexerRules(lexerRulesFile);

    for (const auto &rule : rules) {
        terminals.insert(rule.tokenType);
    }

    return terminals;
}

void GrammarParser::parseProduction(const string &line, Grammar &grammar,
                                    Production *&currentProduction,
                                    set<string> &allSymbols) {
    string trimmed = trim(line);

    // 处理续行（以 | 开头）
    if (!trimmed.empty() && trimmed[0] == '|') {
        if (currentProduction == nullptr) {
            cerr << "Warning: Found '|' without previous production" << endl;
            return;
        }

        string candidate = trim(trimmed.substr(1));
        if (candidate.empty())
            return;

        vector<string> symbols;
        istringstream symbolStream(candidate);
        string symbol;

        while (symbolStream >> symbol) {
            symbol = trim(symbol);
            if (!symbol.empty() && symbol != "ε") {
                symbols.push_back(symbol);
                allSymbols.insert(symbol);
            }
        }

        if (symbols.empty() && candidate == "ε") {
            symbols.clear(); // 空产生式用空向量表示
        }

        currentProduction->right.push_back(symbols);
        return;
    }

    // 处理包含 -> 的产生式
    size_t arrowPos = trimmed.find("->");
    if (arrowPos == string::npos)
        return; // 不是产生式行，也不是续行

    string left = trim(trimmed.substr(0, arrowPos));
    string right = trim(trimmed.substr(arrowPos + 2));

    grammar.nonTerminals.insert(left);
    allSymbols.insert(left);

    // 查找或创建产生式
    bool found = false;
    for (auto &prod : grammar.productions) {
        if (prod.left == left) {
            currentProduction = &prod;
            found = true;
            break;
        }
    }

    if (!found) {
        grammar.productions.push_back(Production(left));
        currentProduction = &grammar.productions.back();
    }

    // 解析右侧第一个候选式
    if (!right.empty()) {
        vector<string> symbols;
        istringstream symbolStream(right);
        string symbol;

        while (symbolStream >> symbol) {
            symbol = trim(symbol);
            if (!symbol.empty() && symbol != "ε") {
                symbols.push_back(symbol);
                allSymbols.insert(symbol);
            }
        }

        if (symbols.empty() && right == "ε") {
            symbols.clear(); // 空产生式用空向量表示
        }

        currentProduction->right.push_back(symbols);
    }
}

Grammar GrammarParser::parseGrammar(const string &filename,
                                    const string &lexerRulesFile) {
    Grammar grammar;
    grammar.startSymbol = "";

    // 加载终结符集合（从词法规则文件）
    set<string> terminalSet = loadTerminals(lexerRulesFile);

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return grammar;
    }

    string line;
    Production *currentProduction = nullptr;
    set<string> allSymbols; // 收集所有出现的符号

    // 第一遍：解析产生式，收集所有符号
    while (getline(file, line)) {
        // 去除换行符
        if (!line.empty() && line.back() == '\r' && line.back() == '\n') {
            line.pop_back();
        }

        line = trim(line);

        // 跳过空行和注释
        if (line.empty() || line[0] == '#')
            continue;

        // 处理 %start 指令
        if (line.find("%start") == 0) {
            istringstream iss(line);
            string directive;
            iss >> directive;           // 读取 %start
            iss >> grammar.startSymbol; // 读取开始符号
            continue;
        }

        parseProduction(line, grammar, currentProduction, allSymbols);
    }

    // 第二遍：识别终结符
    for (const string &symbol : allSymbols) {
        if (symbol == "ε")
            continue;

        if (grammar.nonTerminals.find(symbol) != grammar.nonTerminals.end()) {
            // 已经在非终结符集合中
            continue;
        }

        // 如果是词法规则中定义的 token 类型，则是终结符
        if (terminalSet.find(symbol) != terminalSet.end()) {
            grammar.terminals.insert(symbol);
        } else {
            // 否则，报告警告或错误，因为这是一个未知的终结符
            cerr
                << "Warning: Unknown terminal symbol '" << symbol
                << "' found in grammar rules. It is not defined in lexer rules."
                << endl;
            grammar.terminals.insert(symbol);
        }
    }

    // 如果没有显式指定开始符号，使用第一个产生式的左侧
    if (grammar.startSymbol.empty() && !grammar.productions.empty()) {
        grammar.startSymbol = grammar.productions[0].left;
    }

    return grammar;
}
