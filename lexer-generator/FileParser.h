#pragma once
#include <string>
#include <vector>

using namespace std;

struct LexerRule {
    string tokenType;
    string regex;
    bool ignore;
    int priority;
};

class FileParser {
public:
    vector<LexerRule> readLexerRules(const string& filename);
};
