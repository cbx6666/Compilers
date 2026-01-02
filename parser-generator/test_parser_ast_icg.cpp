#include "../lexer-generator/generated_lexer.cpp"
#define TOKEN_DEFINED
#include "generated_parser_ast.cpp"
#include "IRGenerator.h"
#include "ir.h"
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

int main() {

    string testCode = R"(x = 123;
y = 45.67;
if (x > 100) {
    z = 789;
} else {
    w = 0;
    z = 0;
}
while (x < 200) {
    x = x + 1;
}
result = x * y + z / 2;
if (result == 0) {
    result = -result;
})";

    cout << "Source code:\n----------------------------------------\n"
         << testCode
         << "\n----------------------------------------\n";

    vector<Token*> tokens;
    IRBuilder ir;
    try {
        Lexer lexer(testCode);
        tokens = lexer.tokenize();

        cout << "Tokens:\n----------------------------------------\n";
        for (size_t i = 0; i < tokens.size(); ++i) {
            cout << "[" << (i + 1) << "] " << tokens[i]->toString() << "\n";
        }
        cout << "----------------------------------------\n";
        cout << "Total tokens: " << tokens.size() << "\n\n";

        Parser parser(tokens);
        ASTNode* ast = parser.parse();

        IRGenerator irgen;
        irgen.generate(ast, ir);

        cout << "Generated TAC / Quads:\n----------------------------------------\n";
        ir.dump(cout);
        cout << "----------------------------------------\n";

        ofstream tacOut("tac.txt");
        if (tacOut.is_open()) {
            ir.dump(tacOut);
            tacOut.close();
            cout << "TAC written to tac.txt\n";
        } else {
            cerr << "Warning: cannot write tac.txt\n";
        }

        freeAST(ast);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        for (auto t : tokens) delete t;
        return 1;
    }

    for (auto t : tokens) delete t;
    return 0;
}