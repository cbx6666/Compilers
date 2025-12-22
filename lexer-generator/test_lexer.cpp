#include "generated_lexer.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 测试代码
  string testCode = R"(int x = 123;
float y = 45.67;
if (x > 100) {
    return x + y;
}
// 这是一行注释
string name = "hello";)";

  cout << "测试代码：" << endl;
  cout << "========================================" << endl;
  cout << testCode << endl;
  cout << "========================================" << endl;
  cout << "\n开始词法分析...\n" << endl;

  try {
    Lexer lexer(testCode);
    vector<Token *> tokens = lexer.tokenize();

    cout << "识别到的 Token：" << endl;
    cout << "========================================" << endl;

    for (size_t i = 0; i < tokens.size(); i++) {
      Token *token = tokens[i];
      cout << "[" << (i + 1) << "] " << token->toString() << endl;
    }

    cout << "========================================" << endl;
    cout << "总共识别到 " << tokens.size() << " 个 Token" << endl;

    // 清理内存
    for (auto token : tokens) {
      delete token;
    }

  } catch (const exception &e) {
    cerr << "错误: " << e.what() << endl;
    return 1;
  }

  return 0;
}
