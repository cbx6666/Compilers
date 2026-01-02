#include "ParserASTCodeGenerator.h"
#include <sstream>

using namespace std;

static string toValidIdentifier(const string& name) {
    string r = name;
    for (char& c : r) if (c == '\'') c = '_';
    return r;
}

string ParserASTCodeGenerator::generateParserAST(
    const Grammar& grammar,
    const map<string, map<string, ProductionRule>>& table) {

    ostringstream oss;
    oss << "#include <vector>\n";
    oss << "#include <string>\n";
    oss << "#include <stdexcept>\n";
    oss << "#include \"AST.h\"\n\n";
    oss << "using namespace std;\n\n";
    oss << "#ifndef TOKEN_DEFINED\n";
    oss << "#define TOKEN_DEFINED\n";
    oss << "struct Token {\n";
    oss << "    string type;\n";
    oss << "    string value;\n";
    oss << "    int line;\n";
    oss << "    int column;\n";
    oss << "    Token(string t, string v, int l, int c) : type(t), value(v), line(l), column(c) {}\n";
    oss << "    string toString() const {\n";
    oss << "        return \"Token(\" + type + \", \" + value + \", \" + to_string(line) + \", \" + to_string(column) + \")\";\n";
    oss << "    }\n";
    oss << "};\n";
    oss << "#endif\n\n";

    oss << "class Parser {\n";
    oss << "private:\n";
    oss << "    vector<Token*> tokens;\n";
    oss << "    size_t currentPos;\n";
    oss << "    string currentTokenType() { return currentPos >= tokens.size() ? \"$\" : tokens[currentPos]->type; }\n";
    oss << "    string currentTokenValue() { return currentPos >= tokens.size() ? \"\" : tokens[currentPos]->value; }\n";
    oss << "    void consume() { if (currentPos < tokens.size()) currentPos++; }\n";
    oss << "    [[noreturn]] void error(const string& msg) {\n";
    oss << "        string tokenInfo = currentPos < tokens.size() ? tokens[currentPos]->toString() : \"EOF\";\n";
    oss << "        throw runtime_error(\"Parse error: \" + msg + \" at \" + tokenInfo);\n";
    oss << "    }\n\n";
    for (const auto& nt : grammar.nonTerminals) {
        oss << "    ASTNode* parse" << toValidIdentifier(nt) << "();\n";
    }
    oss << "\npublic:\n";
    oss << "    Parser(const vector<Token*>& ts) : tokens(ts), currentPos(0) {}\n";
    string start = grammar.startSymbol.empty() ? *grammar.nonTerminals.begin() : grammar.startSymbol;
    oss << "    ASTNode* parse() {\n";
    oss << "        ASTNode* root = parse" << toValidIdentifier(start) << "();\n";
    oss << "        if (currentTokenType() != \"$\") error(\"Expected EOF\");\n";
    oss << "        return root;\n";
    oss << "    }\n";
    oss << "};\n\n";

    for (const auto& nt : grammar.nonTerminals) {
        oss << "ASTNode* Parser::parse" << toValidIdentifier(nt) << "() {\n";
        oss << "    string lookahead = currentTokenType();\n";
        auto rowIt = table.find(nt);
        if (rowIt == table.end()) {
            oss << "    error(\"No production for " << nt << "\");\n";
            oss << "}\n\n";
            continue;
        }
        bool firstCase = true;
        for (const auto& entry : rowIt->second) {
            const string& terminal = entry.first;
            const ProductionRule& rule = entry.second;
            const vector<string>* candidate = nullptr;
            for (const auto& prod : grammar.productions) {
                if (prod.left == rule.left &&
                    rule.candidateIndex >= 0 &&
                    rule.candidateIndex < (int)prod.right.size()) {
                    candidate = &prod.right[rule.candidateIndex];
                    break;
                }
            }
            if (!candidate) continue;

            oss << (firstCase ? "    if" : "    else if") << " (lookahead == \"" << terminal << "\") {\n";
            firstCase = false;
            oss << "        ASTNode* node = new ASTNode(\"" << nt << "\");\n";
            for (const string& sym : *candidate) {
                if (sym == "ε") continue;
                else if (grammar.nonTerminals.count(sym)) {
                    oss << "        {\n";
                    oss << "            ASTNode* child = parse" << toValidIdentifier(sym) << "();\n";
                    oss << "            node->children.push_back(child);\n";
                    oss << "            lookahead = currentTokenType();\n";
                    oss << "        }\n";
                } else {
                    oss << "        if (lookahead != \"" << sym << "\") error(\"Expected " << sym << "\");\n";
                    oss << "        node->children.push_back(new ASTNode(\"" << sym << "\"));\n";
                    oss << "        node->children.back()->tokenValue = currentTokenValue();\n";
                    oss << "        consume();\n";
                    oss << "        lookahead = currentTokenType();\n";
                }
            }
            oss << "        return node;\n";
            oss << "    }\n";
        }
        oss << "    else {\n";
        oss << "        error(\"Unexpected token for " << nt << "\");\n";
        oss << "    }\n";
        oss << "}\n\n";
    }

    return oss.str();
}