#include "CodeGenerator.h"
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

using namespace std;

string CodeGenerator::generateLexerCode(const vector<LexerRule> &rules,
                                        const vector<shared_ptr<DFA>> &dfas) {
  if (rules.size() != dfas.size()) {
    throw runtime_error("规则数量和DFA数量不匹配");
  }

  ostringstream oss;

  // 生成头文件和基本结构
  oss << "#include <string>\n";
  oss << "#include <vector>\n";
  oss << "#include <stdexcept>\n";
  oss << "\n";
  oss << "using namespace std;\n";
  oss << "\n";

  // 生成Token结构
  oss << generateTokenStruct();
  oss << "\n";

  // 生成Lexer类
  oss << generateLexerClass(rules, dfas);

  return oss.str();
}

string CodeGenerator::generateTokenStruct() {
  ostringstream oss;
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
  return oss.str();
}

string CodeGenerator::generateLexerClass(const vector<LexerRule> &rules,
                                         const vector<shared_ptr<DFA>> &dfas) {
  ostringstream oss;

  oss << "class Lexer {\n";
  oss << "private:\n";
  oss << "    string text;\n";
  oss << "    size_t pos;\n";
  oss << "    int line;\n";
  oss << "    int column;\n";
  oss << "    \n";

  // 为每个DFA生成匹配方法声明
  for (size_t i = 0; i < dfas.size(); i++) {
    oss << "    int matchDFA" << i << "(size_t startPos);\n";
  }
  oss << "    \n";

  oss << "public:\n";
  oss << "    Lexer(const string& input) : text(input), pos(0), line(1), "
         "column(1) {}\n";
  oss << "    \n";
  oss << "    Token* nextToken();\n";
  oss << "    vector<Token*> tokenize();\n";
  oss << "};\n";
  oss << "\n";

  // 生成nextToken方法
  oss << "Token* Lexer::nextToken() {\n";
  oss << "    // 跳过空白字符\n";
  oss << "    while (pos < text.length() && (text[pos] == ' ' || text[pos] == "
         "'\\t' || text[pos] == '\\n' || text[pos] == '\\r')) {\n";
  oss << "        if (text[pos] == '\\n') {\n";
  oss << "            line++;\n";
  oss << "            column = 1;\n";
  oss << "        } else {\n";
  oss << "            column++;\n";
  oss << "        }\n";
  oss << "        pos++;\n";
  oss << "    }\n";
  oss << "    \n";
  oss << "    if (pos >= text.length()) {\n";
  oss << "        return nullptr;\n";
  oss << "    }\n";
  oss << "    \n";
  oss << "    // 尝试匹配每个规则（按文件中的顺序）\n";
  oss << "    int longestLength = 0;\n";
  oss << "    string matchedType;\n";
  oss << "    \n";

  // 为每个规则生成匹配代码（按文件中的顺序）
  for (size_t i = 0; i < rules.size(); i++) {

    oss << "    // 规则: " << rules[i].tokenType;
    if (rules[i].ignore) {
      oss << " (IGNORE)";
    }
    oss << "\n";
    oss << "    int match" << i << " = matchDFA" << i << "(pos);\n";
    if (rules[i].ignore) {
      // IGNORE规则：如果匹配成功，跳过这些字符，不返回token
      oss << "    if (match" << i << " > 0) {\n";
      oss << "        pos += match" << i << ";\n";
      oss << "        column += match" << i << ";\n";
      oss << "        return nextToken();  // 继续匹配下一个token\n";
      oss << "    }\n";
    } else {
      // 普通规则：记录最长匹配
      oss << "    if (match" << i << " > longestLength) {\n";
      oss << "        longestLength = match" << i << ";\n";
      oss << "        matchedType = \"" << rules[i].tokenType << "\";\n";
      oss << "    }\n";
    }
    oss << "    \n";
  }

  oss << "    if (longestLength > 0) {\n";
  oss << "        string value = text.substr(pos, longestLength);\n";
  oss << "        Token* token = new Token(matchedType, value, line, "
         "column);\n";
  oss << "        pos += longestLength;\n";
  oss << "        column += longestLength;\n";
  oss << "        return token;\n";
  oss << "    }\n";
  oss << "    \n";
  oss << "    // 错误：无法识别的字符\n";
  oss << "    throw runtime_error(\"Unexpected character '\" + string(1, "
         "text[pos]) + \"' at line \" + to_string(line) + \", column \" + "
         "to_string(column));\n";
  oss << "}\n";
  oss << "\n";

  // 生成tokenize方法
  oss << "vector<Token*> Lexer::tokenize() {\n";
  oss << "    vector<Token*> tokens;\n";
  oss << "    while (pos < text.length()) {\n";
  oss << "        Token* token = nextToken();\n";
  oss << "        if (token) {\n";
  oss << "            tokens.push_back(token);\n";
  oss << "        } else {\n";
  oss << "            break;\n";
  oss << "        }\n";
  oss << "    }\n";
  oss << "    return tokens;\n";
  oss << "}\n";
  oss << "\n";

  // 为每个DFA生成匹配方法实现
  for (size_t i = 0; i < dfas.size(); i++) {
    oss << generateMatchMethod(static_cast<int>(i), rules[i], dfas[i]);
    oss << "\n";
  }

  return oss.str();
}

string CodeGenerator::generateMatchMethod(int index, const LexerRule &rule,
                                          shared_ptr<DFA> dfa) {
  ostringstream oss;

  // 构建状态ID映射
  map<shared_ptr<DFAState>, int> stateIdMap;
  int stateId = 0;
  for (auto state : dfa->states) {
    stateIdMap[state] = stateId++;
  }

  int startStateId = stateIdMap[dfa->start];

  // 生成状态转换表
  oss << "int Lexer::matchDFA" << index << "(size_t startPos) {\n";
  oss << "    int state = " << startStateId << ";\n";
  oss << "    size_t currentPos = startPos;\n";
  oss << "    size_t lastAcceptingPos = string::npos;\n";
  oss << "    \n";

  // 生成接受状态集合
  set<int> acceptingStateIds;
  for (auto state : dfa->states) {
    if (state->isAccepting) {
      acceptingStateIds.insert(stateIdMap[state]);
    }
  }

  oss << "    // 接受状态集合\n";
  oss << "    bool accepting[" << stateId << "] = {";
  for (int i = 0; i < stateId; i++) {
    if (i > 0)
      oss << ", ";
    oss << (acceptingStateIds.find(i) != acceptingStateIds.end() ? "true"
                                                                 : "false");
  }
  oss << "};\n";
  oss << "    \n";

  // 生成转换表
  oss << "    // 状态转换表: transitions[state][char] = nextState\n";
  oss << "    int transitions[" << stateId << "][256];\n";
  oss << "    // 初始化为-1（无转换）\n";
  oss << "    for (int i = 0; i < " << stateId << "; i++) {\n";
  oss << "        for (int j = 0; j < 256; j++) {\n";
  oss << "            transitions[i][j] = -1;\n";
  oss << "        }\n";
  oss << "    }\n";
  oss << "    \n";

  // 填充转换表
  for (auto state : dfa->states) {
    int fromId = stateIdMap[state];
    for (auto &pair : state->transitions) {
      char c = pair.first;
      auto targetState = pair.second;
      int toId = stateIdMap[targetState];
      oss << "    transitions[" << fromId << "]["
          << static_cast<int>(static_cast<unsigned char>(c)) << "] = " << toId
          << ";\n";
    }
  }

  oss << "    \n";
  oss << "    // 执行DFA匹配\n";
  oss << "    while (currentPos < text.length()) {\n";
  oss << "        unsigned char ch = static_cast<unsigned "
         "char>(text[currentPos]);\n";
  oss << "        int nextState = transitions[state][ch];\n";
  oss << "        if (nextState == -1) {\n";
  oss << "            break;\n";
  oss << "        }\n";
  oss << "        state = nextState;\n";
  oss << "        currentPos++;\n";
  oss << "        if (accepting[state]) {\n";
  oss << "            lastAcceptingPos = currentPos;\n";
  oss << "        }\n";
  oss << "    }\n";
  oss << "    \n";
  oss << "    if (lastAcceptingPos != string::npos) {\n";
  oss << "        return static_cast<int>(lastAcceptingPos - startPos);\n";
  oss << "    }\n";
  oss << "    return 0;\n";
  oss << "}\n";

  return oss.str();
}
