#include "../lexer-generator/generated_lexer.cpp"
#define TOKEN_DEFINED
#include "generated_parser.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 测试代码：包含多种语句类型（赋值、if、while、块、表达式）
    string testCode = R"(x = 123;
y = 45.67;
if (x > 100) {
    z = 789;
} else {
    w = 0;
}
while (x < 200) {
    x = x + 1;
}
result = x * y + z / 2;
if (result == 0) {
    result = -result;
})";

    cout << "测试代码：" << endl;
    cout << "========================================" << endl;
    cout << testCode << endl;
    cout << "========================================" << endl;
    cout << "\n开始词法分析..." << endl;

    vector<Token *> tokens;

    try {
        // 第一步：词法分析
        Lexer lexer(testCode);
        tokens = lexer.tokenize();

        cout << "识别到的 Token：" << endl;
        cout << "========================================" << endl;
        for (size_t i = 0; i < tokens.size(); i++) {
            cout << "[" << (i + 1) << "] " << tokens[i]->toString() << endl;
        }
        cout << "========================================" << endl;
        cout << "总共识别到 " << tokens.size() << " 个 Token" << endl;
        cout << "\n开始语法分析..." << endl;

        // 第二步：语法分析
        Parser parser(tokens);
        parser.parse();

        cout << "========================================" << endl;
        cout << "语法分析成功！代码符合语法规则。" << endl;
        cout << "========================================" << endl;

    } catch (const exception &e) {
        cerr << "\n错误: " << e.what() << endl;
        return 1;
    }

    // 清理内存
    for (auto token : tokens) {
        delete token;
    }

    return 0;
}
