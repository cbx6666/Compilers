#include <vector>
#include <string>
#include <stdexcept>
#include "AST.h"

using namespace std;

#ifndef TOKEN_DEFINED
#define TOKEN_DEFINED
struct Token {
    string type;
    string value;
    int line;
    int column;
    Token(string t, string v, int l, int c) : type(t), value(v), line(l), column(c) {}
    string toString() const {
        return "Token(" + type + ", " + value + ", " + to_string(line) + ", " + to_string(column) + ")";
    }
};
#endif

class Parser {
private:
    vector<Token*> tokens;
    size_t currentPos;
    string currentTokenType() { return currentPos >= tokens.size() ? "$" : tokens[currentPos]->type; }
    string currentTokenValue() { return currentPos >= tokens.size() ? "" : tokens[currentPos]->value; }
    void consume() { if (currentPos < tokens.size()) currentPos++; }
    [[noreturn]] void error(const string& msg) {
        string tokenInfo = currentPos < tokens.size() ? tokens[currentPos]->toString() : "EOF";
        throw runtime_error("Parse error: " + msg + " at " + tokenInfo);
    }

    ASTNode* parseAddExpr();
    ASTNode* parseAddExpr_();
    ASTNode* parseAssignStmt();
    ASTNode* parseBlock();
    ASTNode* parseElsePart();
    ASTNode* parseExpr();
    ASTNode* parseIfStmt();
    ASTNode* parseMulExpr();
    ASTNode* parseMulExpr_();
    ASTNode* parsePrimary();
    ASTNode* parseProgram();
    ASTNode* parseRelExpr();
    ASTNode* parseRelExpr_();
    ASTNode* parseStmt();
    ASTNode* parseStmtList();
    ASTNode* parseUnaryExpr();
    ASTNode* parseWhileStmt();

public:
    Parser(const vector<Token*>& ts) : tokens(ts), currentPos(0) {}
    ASTNode* parse() {
        ASTNode* root = parseProgram();
        if (currentTokenType() != "$") error("Expected EOF");
        return root;
    }
};

ASTNode* Parser::parseAddExpr() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("AddExpr");
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("AddExpr");
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("AddExpr");
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("AddExpr");
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("AddExpr");
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for AddExpr");
    }
}

ASTNode* Parser::parseAddExpr_() {
    string lookahead = currentTokenType();
    if (lookahead == "EQUAL_EQUAL") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "GREATER") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "GREATER_EQUAL") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "LESS") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "LESS_EQUAL") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("AddExpr'");
        if (lookahead != "MINUS") error("Expected MINUS");
        node->children.push_back(new ASTNode("MINUS"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NOT_EQUAL") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "PLUS") {
        ASTNode* node = new ASTNode("AddExpr'");
        if (lookahead != "PLUS") error("Expected PLUS");
        node->children.push_back(new ASTNode("PLUS"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseMulExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseAddExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "RPAREN") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else if (lookahead == "SEMICOLON") {
        ASTNode* node = new ASTNode("AddExpr'");
        return node;
    }
    else {
        error("Unexpected token for AddExpr'");
    }
}

ASTNode* Parser::parseAssignStmt() {
    string lookahead = currentTokenType();
    if (lookahead == "ID") {
        ASTNode* node = new ASTNode("AssignStmt");
        if (lookahead != "ID") error("Expected ID");
        node->children.push_back(new ASTNode("ID"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        if (lookahead != "EQUAL") error("Expected EQUAL");
        node->children.push_back(new ASTNode("EQUAL"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        if (lookahead != "SEMICOLON") error("Expected SEMICOLON");
        node->children.push_back(new ASTNode("SEMICOLON"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else {
        error("Unexpected token for AssignStmt");
    }
}

ASTNode* Parser::parseBlock() {
    string lookahead = currentTokenType();
    if (lookahead == "LBRACE") {
        ASTNode* node = new ASTNode("Block");
        if (lookahead != "LBRACE") error("Expected LBRACE");
        node->children.push_back(new ASTNode("LBRACE"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        if (lookahead != "RBRACE") error("Expected RBRACE");
        node->children.push_back(new ASTNode("RBRACE"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else {
        error("Unexpected token for Block");
    }
}

ASTNode* Parser::parseElsePart() {
    string lookahead = currentTokenType();
    if (lookahead == "$") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else if (lookahead == "ELSE") {
        ASTNode* node = new ASTNode("ElsePart");
        if (lookahead != "ELSE") error("Expected ELSE");
        node->children.push_back(new ASTNode("ELSE"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else if (lookahead == "IF") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else if (lookahead == "LBRACE") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else if (lookahead == "RBRACE") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else if (lookahead == "WHILE") {
        ASTNode* node = new ASTNode("ElsePart");
        return node;
    }
    else {
        error("Unexpected token for ElsePart");
    }
}

ASTNode* Parser::parseExpr() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("Expr");
        {
            ASTNode* child = parseRelExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("Expr");
        {
            ASTNode* child = parseRelExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("Expr");
        {
            ASTNode* child = parseRelExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("Expr");
        {
            ASTNode* child = parseRelExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("Expr");
        {
            ASTNode* child = parseRelExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for Expr");
    }
}

ASTNode* Parser::parseIfStmt() {
    string lookahead = currentTokenType();
    if (lookahead == "IF") {
        ASTNode* node = new ASTNode("IfStmt");
        if (lookahead != "IF") error("Expected IF");
        node->children.push_back(new ASTNode("IF"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        if (lookahead != "LPAREN") error("Expected LPAREN");
        node->children.push_back(new ASTNode("LPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        if (lookahead != "RPAREN") error("Expected RPAREN");
        node->children.push_back(new ASTNode("RPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseElsePart();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for IfStmt");
    }
}

ASTNode* Parser::parseMulExpr() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("MulExpr");
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("MulExpr");
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("MulExpr");
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("MulExpr");
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("MulExpr");
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for MulExpr");
    }
}

ASTNode* Parser::parseMulExpr_() {
    string lookahead = currentTokenType();
    if (lookahead == "DIVIDE") {
        ASTNode* node = new ASTNode("MulExpr'");
        if (lookahead != "DIVIDE") error("Expected DIVIDE");
        node->children.push_back(new ASTNode("DIVIDE"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "EQUAL_EQUAL") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "GREATER") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "GREATER_EQUAL") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "LESS") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "LESS_EQUAL") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "MOD") {
        ASTNode* node = new ASTNode("MulExpr'");
        if (lookahead != "MOD") error("Expected MOD");
        node->children.push_back(new ASTNode("MOD"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MULTIPLY") {
        ASTNode* node = new ASTNode("MulExpr'");
        if (lookahead != "MULTIPLY") error("Expected MULTIPLY");
        node->children.push_back(new ASTNode("MULTIPLY"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseMulExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NOT_EQUAL") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "PLUS") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "RPAREN") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else if (lookahead == "SEMICOLON") {
        ASTNode* node = new ASTNode("MulExpr'");
        return node;
    }
    else {
        error("Unexpected token for MulExpr'");
    }
}

ASTNode* Parser::parsePrimary() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("Primary");
        if (lookahead != "FLOAT_NUMBER") error("Expected FLOAT_NUMBER");
        node->children.push_back(new ASTNode("FLOAT_NUMBER"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("Primary");
        if (lookahead != "ID") error("Expected ID");
        node->children.push_back(new ASTNode("ID"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("Primary");
        if (lookahead != "LPAREN") error("Expected LPAREN");
        node->children.push_back(new ASTNode("LPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        if (lookahead != "RPAREN") error("Expected RPAREN");
        node->children.push_back(new ASTNode("RPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("Primary");
        if (lookahead != "NUMBER") error("Expected NUMBER");
        node->children.push_back(new ASTNode("NUMBER"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        return node;
    }
    else {
        error("Unexpected token for Primary");
    }
}

ASTNode* Parser::parseProgram() {
    string lookahead = currentTokenType();
    if (lookahead == "$") {
        ASTNode* node = new ASTNode("Program");
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("Program");
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "IF") {
        ASTNode* node = new ASTNode("Program");
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LBRACE") {
        ASTNode* node = new ASTNode("Program");
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "WHILE") {
        ASTNode* node = new ASTNode("Program");
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for Program");
    }
}

ASTNode* Parser::parseRelExpr() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("RelExpr");
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("RelExpr");
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("RelExpr");
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("RelExpr");
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("RelExpr");
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for RelExpr");
    }
}

ASTNode* Parser::parseRelExpr_() {
    string lookahead = currentTokenType();
    if (lookahead == "EQUAL_EQUAL") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "EQUAL_EQUAL") error("Expected EQUAL_EQUAL");
        node->children.push_back(new ASTNode("EQUAL_EQUAL"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "GREATER") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "GREATER") error("Expected GREATER");
        node->children.push_back(new ASTNode("GREATER"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "GREATER_EQUAL") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "GREATER_EQUAL") error("Expected GREATER_EQUAL");
        node->children.push_back(new ASTNode("GREATER_EQUAL"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LESS") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "LESS") error("Expected LESS");
        node->children.push_back(new ASTNode("LESS"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LESS_EQUAL") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "LESS_EQUAL") error("Expected LESS_EQUAL");
        node->children.push_back(new ASTNode("LESS_EQUAL"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NOT_EQUAL") {
        ASTNode* node = new ASTNode("RelExpr'");
        if (lookahead != "NOT_EQUAL") error("Expected NOT_EQUAL");
        node->children.push_back(new ASTNode("NOT_EQUAL"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseAddExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseRelExpr_();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "RPAREN") {
        ASTNode* node = new ASTNode("RelExpr'");
        return node;
    }
    else if (lookahead == "SEMICOLON") {
        ASTNode* node = new ASTNode("RelExpr'");
        return node;
    }
    else {
        error("Unexpected token for RelExpr'");
    }
}

ASTNode* Parser::parseStmt() {
    string lookahead = currentTokenType();
    if (lookahead == "ID") {
        ASTNode* node = new ASTNode("Stmt");
        {
            ASTNode* child = parseAssignStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "IF") {
        ASTNode* node = new ASTNode("Stmt");
        {
            ASTNode* child = parseIfStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LBRACE") {
        ASTNode* node = new ASTNode("Stmt");
        {
            ASTNode* child = parseBlock();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "WHILE") {
        ASTNode* node = new ASTNode("Stmt");
        {
            ASTNode* child = parseWhileStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for Stmt");
    }
}

ASTNode* Parser::parseStmtList() {
    string lookahead = currentTokenType();
    if (lookahead == "$") {
        ASTNode* node = new ASTNode("StmtList");
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("StmtList");
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "IF") {
        ASTNode* node = new ASTNode("StmtList");
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LBRACE") {
        ASTNode* node = new ASTNode("StmtList");
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "RBRACE") {
        ASTNode* node = new ASTNode("StmtList");
        return node;
    }
    else if (lookahead == "WHILE") {
        ASTNode* node = new ASTNode("StmtList");
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        {
            ASTNode* child = parseStmtList();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for StmtList");
    }
}

ASTNode* Parser::parseUnaryExpr() {
    string lookahead = currentTokenType();
    if (lookahead == "FLOAT_NUMBER") {
        ASTNode* node = new ASTNode("UnaryExpr");
        {
            ASTNode* child = parsePrimary();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "ID") {
        ASTNode* node = new ASTNode("UnaryExpr");
        {
            ASTNode* child = parsePrimary();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "LPAREN") {
        ASTNode* node = new ASTNode("UnaryExpr");
        {
            ASTNode* child = parsePrimary();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "MINUS") {
        ASTNode* node = new ASTNode("UnaryExpr");
        if (lookahead != "MINUS") error("Expected MINUS");
        node->children.push_back(new ASTNode("MINUS"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseUnaryExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else if (lookahead == "NUMBER") {
        ASTNode* node = new ASTNode("UnaryExpr");
        {
            ASTNode* child = parsePrimary();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for UnaryExpr");
    }
}

ASTNode* Parser::parseWhileStmt() {
    string lookahead = currentTokenType();
    if (lookahead == "WHILE") {
        ASTNode* node = new ASTNode("WhileStmt");
        if (lookahead != "WHILE") error("Expected WHILE");
        node->children.push_back(new ASTNode("WHILE"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        if (lookahead != "LPAREN") error("Expected LPAREN");
        node->children.push_back(new ASTNode("LPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseExpr();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        if (lookahead != "RPAREN") error("Expected RPAREN");
        node->children.push_back(new ASTNode("RPAREN"));
        node->children.back()->tokenValue = currentTokenValue();
        consume();
        lookahead = currentTokenType();
        {
            ASTNode* child = parseStmt();
            node->children.push_back(child);
            lookahead = currentTokenType();
        }
        return node;
    }
    else {
        error("Unexpected token for WhileStmt");
    }
}

