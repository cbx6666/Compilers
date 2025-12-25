#include <vector>
#include <string>
#include <stdexcept>

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
    
    // 获取当前 token 的类型（如果已结束则返回 "$"）
    string currentTokenType() {
        if (currentPos >= tokens.size()) {
            return "$";
        }
        return tokens[currentPos]->type;
    }
    
    // 消耗当前 token（移动到下一个）
    void consume() {
        if (currentPos < tokens.size()) {
            currentPos++;
        }
    }
    
    // 抛出语法错误
    void error(const string& msg) {
        string tokenInfo = currentPos < tokens.size() ? 
            tokens[currentPos]->toString() : "EOF";
        throw runtime_error("Parse error: " + msg + " at " + tokenInfo);
    }
    
    void parseAddExpr();
    void parseAddExpr_();
    void parseAssignStmt();
    void parseBlock();
    void parseElsePart();
    void parseExpr();
    void parseIfStmt();
    void parseMulExpr();
    void parseMulExpr_();
    void parsePrimary();
    void parseProgram();
    void parseRelExpr();
    void parseRelExpr_();
    void parseStmt();
    void parseStmtList();
    void parseUnaryExpr();
    void parseWhileStmt();
    
  public:
    Parser(const vector<Token*>& tokenList) : tokens(tokenList), currentPos(0) {}
    
    // 开始解析
    void parse() {
        parseProgram();
        if (currentTokenType() != "$") {
            error("Expected EOF");
        }
    }
};

void Parser::parseAddExpr() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "MINUS") {
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for AddExpr, expected one of: FLOAT_NUMBER, ID, LPAREN, MINUS, NUMBER");
    }
}

void Parser::parseAddExpr_() {
    string lookahead = currentTokenType();
    
    if (lookahead == "EQUAL_EQUAL") {
    } else if (lookahead == "GREATER") {
    } else if (lookahead == "GREATER_EQUAL") {
    } else if (lookahead == "LESS") {
    } else if (lookahead == "LESS_EQUAL") {
    } else if (lookahead == "MINUS") {
        consume();
        lookahead = currentTokenType();
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NOT_EQUAL") {
    } else if (lookahead == "PLUS") {
        consume();
        lookahead = currentTokenType();
        parseMulExpr();
        lookahead = currentTokenType();
        parseAddExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "RPAREN") {
    } else if (lookahead == "SEMICOLON") {
    } else {
        error("Unexpected token for AddExpr', expected one of: EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, MINUS, NOT_EQUAL, PLUS, RPAREN, SEMICOLON");
    }
}

void Parser::parseAssignStmt() {
    string lookahead = currentTokenType();
    
    if (lookahead == "ID") {
        consume();
        lookahead = currentTokenType();
        if (lookahead != "EQUAL") {
            error("Expected EQUAL");
        }
        consume();
        lookahead = currentTokenType();
        parseExpr();
        lookahead = currentTokenType();
        if (lookahead != "SEMICOLON") {
            error("Expected SEMICOLON");
        }
        consume();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for AssignStmt, expected one of: ID");
    }
}

void Parser::parseBlock() {
    string lookahead = currentTokenType();
    
    if (lookahead == "LBRACE") {
        consume();
        lookahead = currentTokenType();
        parseStmtList();
        lookahead = currentTokenType();
        if (lookahead != "RBRACE") {
            error("Expected RBRACE");
        }
        consume();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for Block, expected one of: LBRACE");
    }
}

void Parser::parseElsePart() {
    string lookahead = currentTokenType();
    
    if (lookahead == "$") {
    } else if (lookahead == "ELSE") {
        consume();
        lookahead = currentTokenType();
        parseStmt();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
    } else if (lookahead == "IF") {
    } else if (lookahead == "LBRACE") {
    } else if (lookahead == "RBRACE") {
    } else if (lookahead == "WHILE") {
    } else {
        error("Unexpected token for ElsePart, expected one of: $, ELSE, ID, IF, LBRACE, RBRACE, WHILE");
    }
}

void Parser::parseExpr() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        parseRelExpr();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parseRelExpr();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        parseRelExpr();
        lookahead = currentTokenType();
    } else if (lookahead == "MINUS") {
        parseRelExpr();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        parseRelExpr();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for Expr, expected one of: FLOAT_NUMBER, ID, LPAREN, MINUS, NUMBER");
    }
}

void Parser::parseIfStmt() {
    string lookahead = currentTokenType();
    
    if (lookahead == "IF") {
        consume();
        lookahead = currentTokenType();
        if (lookahead != "LPAREN") {
            error("Expected LPAREN");
        }
        consume();
        lookahead = currentTokenType();
        parseExpr();
        lookahead = currentTokenType();
        if (lookahead != "RPAREN") {
            error("Expected RPAREN");
        }
        consume();
        lookahead = currentTokenType();
        parseStmt();
        lookahead = currentTokenType();
        parseElsePart();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for IfStmt, expected one of: IF");
    }
}

void Parser::parseMulExpr() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "MINUS") {
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for MulExpr, expected one of: FLOAT_NUMBER, ID, LPAREN, MINUS, NUMBER");
    }
}

void Parser::parseMulExpr_() {
    string lookahead = currentTokenType();
    
    if (lookahead == "DIVIDE") {
        consume();
        lookahead = currentTokenType();
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "EQUAL_EQUAL") {
    } else if (lookahead == "GREATER") {
    } else if (lookahead == "GREATER_EQUAL") {
    } else if (lookahead == "LESS") {
    } else if (lookahead == "LESS_EQUAL") {
    } else if (lookahead == "MINUS") {
    } else if (lookahead == "MOD") {
        consume();
        lookahead = currentTokenType();
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "MULTIPLY") {
        consume();
        lookahead = currentTokenType();
        parseUnaryExpr();
        lookahead = currentTokenType();
        parseMulExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NOT_EQUAL") {
    } else if (lookahead == "PLUS") {
    } else if (lookahead == "RPAREN") {
    } else if (lookahead == "SEMICOLON") {
    } else {
        error("Unexpected token for MulExpr', expected one of: DIVIDE, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, MINUS, MOD, MULTIPLY, NOT_EQUAL, PLUS, RPAREN, SEMICOLON");
    }
}

void Parser::parsePrimary() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        consume();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        consume();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        consume();
        lookahead = currentTokenType();
        parseExpr();
        lookahead = currentTokenType();
        if (lookahead != "RPAREN") {
            error("Expected RPAREN");
        }
        consume();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        consume();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for Primary, expected one of: FLOAT_NUMBER, ID, LPAREN, NUMBER");
    }
}

void Parser::parseProgram() {
    string lookahead = currentTokenType();
    
    if (lookahead == "$") {
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "IF") {
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "LBRACE") {
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "WHILE") {
        parseStmtList();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for Program, expected one of: $, ID, IF, LBRACE, WHILE");
    }
}

void Parser::parseRelExpr() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "MINUS") {
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for RelExpr, expected one of: FLOAT_NUMBER, ID, LPAREN, MINUS, NUMBER");
    }
}

void Parser::parseRelExpr_() {
    string lookahead = currentTokenType();
    
    if (lookahead == "EQUAL_EQUAL") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "GREATER") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "GREATER_EQUAL") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "LESS") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "LESS_EQUAL") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "NOT_EQUAL") {
        consume();
        lookahead = currentTokenType();
        parseAddExpr();
        lookahead = currentTokenType();
        parseRelExpr_();
        lookahead = currentTokenType();
    } else if (lookahead == "RPAREN") {
    } else if (lookahead == "SEMICOLON") {
    } else {
        error("Unexpected token for RelExpr', expected one of: EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, NOT_EQUAL, RPAREN, SEMICOLON");
    }
}

void Parser::parseStmt() {
    string lookahead = currentTokenType();
    
    if (lookahead == "ID") {
        parseAssignStmt();
        lookahead = currentTokenType();
    } else if (lookahead == "IF") {
        parseIfStmt();
        lookahead = currentTokenType();
    } else if (lookahead == "LBRACE") {
        parseBlock();
        lookahead = currentTokenType();
    } else if (lookahead == "WHILE") {
        parseWhileStmt();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for Stmt, expected one of: ID, IF, LBRACE, WHILE");
    }
}

void Parser::parseStmtList() {
    string lookahead = currentTokenType();
    
    if (lookahead == "$") {
    } else if (lookahead == "ID") {
        parseStmt();
        lookahead = currentTokenType();
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "IF") {
        parseStmt();
        lookahead = currentTokenType();
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "LBRACE") {
        parseStmt();
        lookahead = currentTokenType();
        parseStmtList();
        lookahead = currentTokenType();
    } else if (lookahead == "RBRACE") {
    } else if (lookahead == "WHILE") {
        parseStmt();
        lookahead = currentTokenType();
        parseStmtList();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for StmtList, expected one of: $, ID, IF, LBRACE, RBRACE, WHILE");
    }
}

void Parser::parseUnaryExpr() {
    string lookahead = currentTokenType();
    
    if (lookahead == "FLOAT_NUMBER") {
        parsePrimary();
        lookahead = currentTokenType();
    } else if (lookahead == "ID") {
        parsePrimary();
        lookahead = currentTokenType();
    } else if (lookahead == "LPAREN") {
        parsePrimary();
        lookahead = currentTokenType();
    } else if (lookahead == "MINUS") {
        consume();
        lookahead = currentTokenType();
        parseUnaryExpr();
        lookahead = currentTokenType();
    } else if (lookahead == "NUMBER") {
        parsePrimary();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for UnaryExpr, expected one of: FLOAT_NUMBER, ID, LPAREN, MINUS, NUMBER");
    }
}

void Parser::parseWhileStmt() {
    string lookahead = currentTokenType();
    
    if (lookahead == "WHILE") {
        consume();
        lookahead = currentTokenType();
        if (lookahead != "LPAREN") {
            error("Expected LPAREN");
        }
        consume();
        lookahead = currentTokenType();
        parseExpr();
        lookahead = currentTokenType();
        if (lookahead != "RPAREN") {
            error("Expected RPAREN");
        }
        consume();
        lookahead = currentTokenType();
        parseStmt();
        lookahead = currentTokenType();
    } else {
        error("Unexpected token for WhileStmt, expected one of: WHILE");
    }
}

