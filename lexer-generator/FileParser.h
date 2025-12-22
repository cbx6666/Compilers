#pragma once
#include <string>
#include <vector>

using namespace std;

struct LexerRule {
  string tokenType;
  string regex;
  bool ignore;
};

class FileParser {
public:
  vector<LexerRule> readLexerRules(const string &filename);
};
