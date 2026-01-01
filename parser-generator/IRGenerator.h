#pragma once
#include "AST.h"
#include "ir.h"
#include <string>

class IRGenerator {
public:
    void generate(ASTNode* root, IRBuilder& ir);
private:
    std::string genExpr(ASTNode* node, IRBuilder& ir);
    void genStmt(ASTNode* node, IRBuilder& ir);
    void genStmtList(ASTNode* node, IRBuilder& ir);
};