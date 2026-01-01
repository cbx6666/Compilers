#pragma once
#include <string>
#include <vector>

struct ASTNode {
    std::string type;                 // 节点类型（通常用非终结符或终结符名）
    std::string tokenValue;           // 终结符文本（仅叶子节点使用）
    std::vector<ASTNode*> children;   // 子节点

    ASTNode(const std::string& t) : type(t) {}
};

// 简单释放工具
inline void freeAST(ASTNode* node) {
    if (!node) return;
    for (auto* c : node->children) freeAST(c);
    delete node;
}