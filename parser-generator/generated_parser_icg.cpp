#include <vector>
#include <string>
#include <stdexcept>
#include "ir.h"

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
    vector<Token *> tokens;
    size_t currentPos;
    IRBuilder &ir;

    string currentTokenType() {
        if (currentPos >= tokens.size()) return "$";
        return tokens[currentPos]->type;
    }
    string currentTokenValue() {
        if (currentPos >= tokens.size()) return "";
        return tokens[currentPos]->value;
    }
    void consume() { if (currentPos < tokens.size()) currentPos++; }
    void expect(const string &type) {
        if (currentTokenType() != type) error("Expected " + type);
        consume();
    }
    [[noreturn]] void error(const string &msg) {
        string tokenInfo = currentPos < tokens.size() ? tokens[currentPos]->toString() : "EOF";
        throw runtime_error("Parse error: " + msg + " at " + tokenInfo);
    }

    // Expr family
    string parseExpr();      // RelExpr
    string parseRelExpr();   // AddExpr (relop AddExpr)*
    string parseAddExpr();   // MulExpr ((+|-) MulExpr)*
    string parseMulExpr();   // UnaryExpr ((*|/|%) UnaryExpr)*
    string parseUnaryExpr(); // [-]UnaryExpr | Primary
    string parsePrimary();   // NUMBER | FLOAT_NUMBER | ID | (Expr)

    // Statements
    void parseProgram();
    void parseStmtList();
    void parseStmt();
    void parseAssignStmt();
    void parseIfStmt();
    void parseElsePart();
    void parseWhileStmt();
    void parseBlock();

  public:
    Parser(const vector<Token *> &tokenList, IRBuilder &builder)
        : tokens(tokenList), currentPos(0), ir(builder) {}

    void parse() {
        parseProgram();
        if (currentTokenType() != "$") error("Expected EOF");
    }
};

// ------ Expressions ------
string Parser::parsePrimary() {
    string la = currentTokenType();
    if (la == "NUMBER" || la == "FLOAT_NUMBER") {
        string v = currentTokenValue();
        consume();
        return v;
    } else if (la == "ID") {
        string id = currentTokenValue();
        consume();
        return id;
    } else if (la == "LPAREN") {
        consume();
        string v = parseExpr();
        expect("RPAREN");
        return v;
    }
    error("Unexpected token for Primary");
}

string Parser::parseUnaryExpr() {
    string la = currentTokenType();
    if (la == "MINUS") {
        consume();
        string rhs = parseUnaryExpr();
        string t = ir.newTemp();
        ir.emit("MINUS", "0", rhs, t); // 0 - rhs
        return t;
    }
    return parsePrimary();
}

string Parser::parseMulExpr() {
    string left = parseUnaryExpr();
    string la = currentTokenType();
    while (la == "MULTIPLY" || la == "DIVIDE" || la == "MOD") {
        string op = la;
        consume();
        string right = parseUnaryExpr();
        string t = ir.newTemp();
        ir.emit(op, left, right, t);
        left = t;
        la = currentTokenType();
    }
    return left;
}

string Parser::parseAddExpr() {
    string left = parseMulExpr();
    string la = currentTokenType();
    while (la == "PLUS" || la == "MINUS") {
        string op = la;
        consume();
        string right = parseMulExpr();
        string t = ir.newTemp();
        ir.emit(op, left, right, t);
        left = t;
        la = currentTokenType();
    }
    return left;
}

string Parser::parseRelExpr() {
    string left = parseAddExpr();
    string la = currentTokenType();
    while (la == "EQUAL_EQUAL" || la == "NOT_EQUAL" ||
           la == "GREATER" || la == "LESS" ||
           la == "GREATER_EQUAL" || la == "LESS_EQUAL") {
        string op = la;
        consume();
        string right = parseAddExpr();
        string t = ir.newTemp();
        ir.emit(op, left, right, t);
        left = t;
        la = currentTokenType();
    }
    return left;
}

string Parser::parseExpr() { return parseRelExpr(); }

// ------ Statements ------
void Parser::parseAssignStmt() {
    if (currentTokenType() != "ID") error("Expected ID at AssignStmt");
    string id = currentTokenValue();
    consume();
    expect("EQUAL");
    string val = parseExpr();
    expect("SEMICOLON");
    ir.emit("=", val, "", id);
}

void Parser::parseBlock() {
    expect("LBRACE");
    parseStmtList();
    expect("RBRACE");
}

void Parser::parseElsePart() {
    string la = currentTokenType();
    if (la == "ELSE") {
        consume();
        parseStmt();
    } else if (la == "ID" || la == "IF" || la == "LBRACE" ||
               la == "WHILE" || la == "RBRACE" || la == "$") {
        // epsilon
    } else {
        error("Unexpected token for ElsePart");
    }
}

void Parser::parseIfStmt() {
    expect("IF");
    expect("LPAREN");
    string cond = parseExpr();
    expect("RPAREN");

    string lElse = ir.newLabel();
    string lEnd  = ir.newLabel();

    ir.emit("IF_FALSE", cond, "", lElse);
    parseStmt();
    ir.emit("GOTO", "", "", lEnd);
    ir.emit("LABEL", "", "", lElse);
    parseElsePart();
    ir.emit("LABEL", "", "", lEnd);
}

void Parser::parseWhileStmt() {
    string lBegin = ir.newLabel();
    string lEnd   = ir.newLabel();

    ir.emit("LABEL", "", "", lBegin);
    expect("WHILE");
    expect("LPAREN");
    string cond = parseExpr();
    expect("RPAREN");
    ir.emit("IF_FALSE", cond, "", lEnd);
    parseStmt();
    ir.emit("GOTO", "", "", lBegin);
    ir.emit("LABEL", "", "", lEnd);
}

void Parser::parseStmt() {
    string la = currentTokenType();
    if (la == "ID") {
        parseAssignStmt();
    } else if (la == "IF") {
        parseIfStmt();
    } else if (la == "WHILE") {
        parseWhileStmt();
    } else if (la == "LBRACE") {
        parseBlock();
    } else {
        error("Unexpected token for Stmt");
    }
}

void Parser::parseStmtList() {
    string la = currentTokenType();
    while (la == "ID" || la == "IF" || la == "WHILE" || la == "LBRACE") {
        parseStmt();
        la = currentTokenType();
    }
    // epsilon
}

void Parser::parseProgram() {
    parseStmtList();
    // epsilon allowed
}