#pragma once
#include "RegexAST.h"
#include <string>

using namespace std;

class RegexParser {
public:
    // 解析正则表达式字符串，返回AST根节点
    shared_ptr<ASTNode> parse(const string& regex);

private:
    string input;
    size_t pos;  // 当前解析位置

    // 递归下降解析
    shared_ptr<ASTNode> parseUnion();      // 解析 |
    shared_ptr<ASTNode> parseConcat();     // 解析连接
    shared_ptr<ASTNode> parseRepeat();     // 解析 * + ?
    shared_ptr<ASTNode> parseAtom();       // 解析原子（字符、字符类、括号）
    shared_ptr<ASTNode> parseCharset();    // 解析 [...]
    
    char peek();        // 查看当前字符
    char advance();     // 前进一个字符
    bool isEnd();       // 是否到末尾
    bool match(char c); // 匹配并前进
};
