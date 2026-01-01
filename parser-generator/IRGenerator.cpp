#include "IRGenerator.h"
#include <stdexcept>

using namespace std;

static ASTNode* childAt(ASTNode* n, size_t i) {
    if (!n || i >= n->children.size()) return nullptr;
    return n->children[i];
}

void IRGenerator::generate(ASTNode* root, IRBuilder& ir) {
    if (!root) throw runtime_error("AST is null");
    if (root->type == "Program") {
        genStmtList(childAt(root, 0), ir);
    } else {
        throw runtime_error("Unsupported root: " + root->type);
    }
}

void IRGenerator::genStmtList(ASTNode* node, IRBuilder& ir) {
    if (!node) return;
    // StmtList -> (Stmt StmtList) | ε
    if (node->children.empty()) return;
    genStmt(childAt(node, 0), ir);
    if (node->children.size() > 1) genStmtList(childAt(node, 1), ir);
}

void IRGenerator::genStmt(ASTNode* node, IRBuilder& ir) {
    if (!node) return;
    // Stmt -> AssignStmt | IfStmt | WhileStmt | Block
    ASTNode* first = childAt(node, 0);
    if (!first) throw runtime_error("Malformed Stmt");
    const string& t = first->type;
    if (t == "AssignStmt") {
        // AssignStmt -> ID EQUAL Expr SEMICOLON
        string id = childAt(first, 0)->tokenValue;
        ASTNode* exprNode = childAt(first, 2);
        string val = genExpr(exprNode, ir);
        ir.emit("=", val, "", id);
    } else if (t == "IfStmt") {
        // IfStmt -> IF LPAREN Expr RPAREN Stmt ElsePart
        ASTNode* condNode = childAt(first, 2);
        ASTNode* thenNode = childAt(first, 4);
        ASTNode* elsePart = childAt(first, 5);

        string cond = genExpr(condNode, ir);
        string lElse = ir.newLabel();
        string lEnd  = ir.newLabel();
        ir.emit("IF_FALSE", cond, "", lElse);
        genStmt(thenNode, ir);
        ir.emit("GOTO", "", "", lEnd);
        ir.emit("LABEL", "", "", lElse);
        if (elsePart && !elsePart->children.empty()) {
            // ElsePart -> ELSE Stmt | ε
            genStmt(childAt(elsePart, 1), ir);
        }
        ir.emit("LABEL", "", "", lEnd);
    } else if (t == "WhileStmt") {
        // WhileStmt -> WHILE LPAREN Expr RPAREN Stmt
        ASTNode* condNode = childAt(first, 2);
        ASTNode* bodyNode = childAt(first, 4);

        string lBegin = ir.newLabel();
        string lEnd   = ir.newLabel();
        ir.emit("LABEL", "", "", lBegin);
        string cond = genExpr(condNode, ir);
        ir.emit("IF_FALSE", cond, "", lEnd);
        genStmt(bodyNode, ir);
        ir.emit("GOTO", "", "", lBegin);
        ir.emit("LABEL", "", "", lEnd);
    } else if (t == "Block") {
        // Block -> LBRACE StmtList RBRACE
        genStmtList(childAt(first, 1), ir);
    } else {
        throw runtime_error("Unsupported Stmt kind: " + t);
    }
}

string IRGenerator::genExpr(ASTNode* node, IRBuilder& ir) {
    if (!node) throw runtime_error("Null Expr node");
    // Expr -> RelExpr ; RelExpr is built with left recursion removed but AST keeps hierarchy
    // We'll pattern-match bottom-up: Primary / Unary / Mul / Add / Rel
    const string& t = node->type;

    // Leaf terminals
    if (t == "NUMBER" || t == "FLOAT_NUMBER" || t == "ID") {
        return node->tokenValue;
    }

    // Primary
    if (t == "Primary") {
        if (node->children.size() == 1) { // NUMBER/FLOAT/ID
            return genExpr(childAt(node, 0), ir);
        } else if (node->children.size() == 3) { // ( Expr )
            return genExpr(childAt(node, 1), ir);
        }
    }

    // UnaryExpr
    if (t == "UnaryExpr") {
        if (node->children.size() == 2) { // MINUS UnaryExpr
            string rhs = genExpr(childAt(node, 1), ir);
            string tmp = ir.newTemp();
            ir.emit("MINUS", "0", rhs, tmp);
            return tmp;
        }
        return genExpr(childAt(node, 0), ir); // Primary
    }

    // MulExpr / MulExpr'
    if (t == "MulExpr") {
        // structure: UnaryExpr MulExpr'
        string left = genExpr(childAt(node, 0), ir);
        ASTNode* tail = childAt(node, 1);
        while (tail && !tail->children.empty()) {
            // MulExpr' -> (op UnaryExpr MulExpr') | ε
            string op = childAt(tail, 0)->type; // MULTIPLY/DIVIDE/MOD terminal node
            string right = genExpr(childAt(tail, 1), ir);
            string tmp = ir.newTemp();
            ir.emit(op, left, right, tmp);
            left = tmp;
            tail = childAt(tail, 2);
        }
        return left;
    }

    // AddExpr
    if (t == "AddExpr") {
        string left = genExpr(childAt(node, 0), ir); // MulExpr
        ASTNode* tail = childAt(node, 1);
        while (tail && !tail->children.empty()) {
            string op = childAt(tail, 0)->type; // PLUS/MINUS terminal node
            string right = genExpr(childAt(tail, 1), ir);
            string tmp = ir.newTemp();
            ir.emit(op, left, right, tmp);
            left = tmp;
            tail = childAt(tail, 2);
        }
        return left;
    }

    // RelExpr
    if (t == "RelExpr") {
        string left = genExpr(childAt(node, 0), ir); // AddExpr
        ASTNode* tail = childAt(node, 1);
        while (tail && !tail->children.empty()) {
            string op = childAt(tail, 0)->type; // relational op
            string right = genExpr(childAt(tail, 1), ir);
            string tmp = ir.newTemp();
            ir.emit(op, left, right, tmp);
            left = tmp;
            tail = childAt(tail, 2);
        }
        return left;
    }

    // Expr wrapper
    if (t == "Expr") {
        return genExpr(childAt(node, 0), ir);
    }

    throw runtime_error("Unsupported Expr node: " + t);
}