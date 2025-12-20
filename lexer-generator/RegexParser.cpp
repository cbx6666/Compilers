#include "RegexParser.h"
#include <stdexcept>

using namespace std;

shared_ptr<ASTNode> RegexParser::parse(const string& regex) {
    this->input = regex;
    this->pos = 0;
    return this->parseUnion();
}

bool RegexParser::isEnd() {
    return pos >= input.length();
}

char RegexParser::peek() {
    if(isEnd()) return '\0';
    return input[pos];
}

char RegexParser::advance() {
    if(isEnd()) return '\0';
    return input[pos++];
}

bool RegexParser::match(char c) {
    if (peek() == c) {
        advance();
        return true;
    }
    return false;
}

shared_ptr<ASTNode> RegexParser::parseUnion() {
    auto left = parseConcat();

    // 解析 a|b|c
    //       union
    //     /      \ 
    //    union    c
    //  /      \
    // a        b

    // 实现左递归
    while (match('|')) {
        auto right = parseConcat();
        // 创建或节点，将左子树和右子树连接起来，并作为新的左子树
        left = make_shared<UnionNode>(left, right);
    }

    return left;
}

shared_ptr<ASTNode> RegexParser::parseConcat() {
    shared_ptr<ASTNode> left = nullptr;

    // 实现左递归
    while (!isEnd() && peek() != '|' && peek() != ')') {
        auto node = parseRepeat();
        if (!left) {
            left = node;
        } else {
            left = make_shared<ConcatNode>(left, node);
        }
    }

    if (!left) {
        return make_shared<EpsilonNode>();
    }

    return left;
}

shared_ptr<ASTNode> RegexParser::parseRepeat() {
    auto atom = parseAtom();

    while(true) {
        if (match('*')) {
            atom = make_shared<StarNode>(atom);
        } else if (match('+')) {
            atom = make_shared<PlusNode>(atom);
        }  else {
            break;
        }
    }

    return atom;
}

shared_ptr<ASTNode> RegexParser::parseAtom() {
    char ch = peek();

    // 处理括号
    if (match('(')) {
        auto node = parseUnion();
        if (!match(')')) {
            throw runtime_error("缺少右括号");
        }
        return node;
    }

    // 处理字符类
    if (match('[')) {
        auto node = parseCharset();
        if (!match(']')) {
            throw runtime_error("缺少右中括号");
        }
        return node;
    }

    // 处理转义字符
    if (match('\\')) {
        if (isEnd()) {
            throw runtime_error("转义字符后缺少字符");
        }
        char escaped = advance();
        // 处理特殊转义
        switch (escaped) {
            case 'n': return make_shared<CharNode>('\n');
            case 't': return make_shared<CharNode>('\t');
            case 'r': return make_shared<CharNode>('\r');
            default:  return make_shared<CharNode>(escaped);
        }
    }

    // 处理单个字符
    if (ch != '\0' && ch != '|' && ch != '(' && ch != ')' && ch != '*' && ch != '+' && ch != '?') {
        advance();  // 跳过当前字符
        return make_shared<CharNode>(ch);
    }
    
    // 如果都不匹配，返回空串
    return make_shared<EpsilonNode>();
}

shared_ptr<ASTNode> RegexParser::parseCharset() {
    // 注意：调用时 [ 已经被 parseAtom() 中的 match('[') 跳过了
    // 所以这里不需要再跳过

    auto charset = make_shared<CharsetNode>();
    while (!isEnd() && peek() != ']') {
        char start;
        
        // 处理转义字符
        if (match('\\')) {
            if (isEnd()) {
                throw runtime_error("转义字符后缺少字符");
            }
            start = advance();
        } else {
            start = advance();
        }

        // 检查是否是范围 a-z
        if (peek() == '-' && pos < input.length() && input[pos + 1] != ']') {
            advance(); // 跳过 '-'
            char end;
            
            // 处理转义
            if (match('\\')) {
                if (isEnd()) {
                    throw runtime_error("转义字符后缺少字符");
                }
                end = advance();
            } else {
                end = advance();
            }
            
            // 添加范围内所有字符
            for (char ch = start; ch <= end; ch++) {
                charset->chars.push_back(ch);
            }
        } else {
            charset->chars.push_back(start);
        }
    }

    return charset;
}
