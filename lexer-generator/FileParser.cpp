#include "FileParser.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

string trim(const string &str) {
    const char *trim_chars = " \t\n";
    size_t start = str.find_first_not_of(trim_chars);
    if (start == string::npos)
        return "";
    size_t end = str.find_last_not_of(trim_chars);
    return str.substr(start, end - start + 1);
}

// 读取词法规则文件
vector<LexerRule> FileParser::readLexerRules(const string &filename) {
    vector<LexerRule> rules;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return rules;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        // 将字符串作为输入流读取
        istringstream iss(line);
        LexerRule rule;

        // 读取token类型
        iss >> rule.tokenType;

        string rest;
        getline(iss, rest);
        rule.ignore = rest.find("IGNORE") != string::npos;

        if (rule.ignore) {
            rest = rest.substr(0, rest.find("IGNORE"));
        }
        rule.regex = trim(rest);

        rules.push_back(rule);
    }

    return rules;
}
