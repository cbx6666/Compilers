#pragma once
#include <string>
#include <memory>
#include <vector>

using namespace std;

// AST节点类型
enum class NodeType {
    CHAR,       // 单个字符，如 'a'
    CONCAT,     // 连接，如 ab
    UNION,      // 并（或），如 a|b
    STAR,       // Kleene闭包，如 a*（0次或多次）
    PLUS,       // 正闭包，如 a+（1次或多次）
    CHARSET,    // 字符类，如 [a-z]
    EPSILON     // 空串 ε
};

class ASTNode {
public:
    NodeType type;
    virtual ~ASTNode() = default;
};

class CharNode : public ASTNode {
public:
    char ch;
    CharNode(char c) : ch(c) { type = NodeType::CHAR; }
};

class ConcatNode : public ASTNode {
public:
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;
    ConcatNode(shared_ptr<ASTNode> l, shared_ptr<ASTNode> r)
        : left(l), right(r) { type = NodeType::CONCAT; }
};

class UnionNode : public ASTNode {
public:
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;
    UnionNode(shared_ptr<ASTNode> l, shared_ptr<ASTNode> r)
        : left(l), right(r) { type = NodeType::UNION; }
};

class StarNode : public ASTNode {
public:
    shared_ptr<ASTNode> child;
    StarNode(shared_ptr<ASTNode> c) : child(c) { type = NodeType::STAR; }
};

class PlusNode : public ASTNode {
public:
    shared_ptr<ASTNode> child;
    PlusNode(shared_ptr<ASTNode> c) : child(c) { type = NodeType::PLUS; }
};

class CharsetNode : public ASTNode {
public:
    vector<char> chars;
    CharsetNode() { type = NodeType::CHARSET; }
};

class EpsilonNode : public ASTNode {
public:
    EpsilonNode() { type = NodeType::EPSILON; }
};
