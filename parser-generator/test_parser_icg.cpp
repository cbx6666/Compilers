#include "../lexer-generator/generated_lexer.cpp"
#define TOKEN_DEFINED
#include "generated_parser_icg.cpp"
#include "ir.h"
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    string testCode = R"(x = 123;
y = 45.67;
if (x > 100) {
    z = 789;
} else {
    w = 0;
    z=0;
}
while (x < 200) {
    x = x + 1;
}
result = x * y + z / 2;
if (result == 0) {
    result = -result;
})";

    cout << "Source code:" << endl;
    cout << "========================================" << endl;
    cout << testCode << endl;
    cout << "========================================" << endl;
    cout << "\nLexing..." << endl;

    vector<Token *> tokens;
    IRBuilder ir;

    try {
        Lexer lexer(testCode);
        tokens = lexer.tokenize();

        cout << "Tokens:" << endl;
        cout << "========================================" << endl;
        for (size_t i = 0; i < tokens.size(); i++) {
            cout << "[" << (i + 1) << "] " << tokens[i]->toString() << endl;
        }
        cout << "========================================" << endl;
        cout << "Total tokens: " << tokens.size() << "\n" << endl;

        cout << "Parsing + generating TAC..." << endl;
        Parser parser(tokens, ir);
        parser.parse();

        cout << "========================================" << endl;
        cout << "Parse success. Generated TAC:" << endl;
        cout << "----------------------------------------" << endl;
        ir.dump(cout);
        cout << "----------------------------------------" << endl;
        cout << "========================================" << endl;

        ofstream tacOut("tac.txt");
        if (tacOut.is_open()) {
            ir.dump(tacOut);
            tacOut.close();
            cout << "TAC written to tac.txt" << endl;
        } else {
            cerr << "Warning: cannot write tac.txt" << endl;
        }

    } catch (const exception &e) {
        cerr << "\nError: " << e.what() << endl;
        for (auto t : tokens) delete t;
        return 1;
    }

    for (auto t : tokens) delete t;
    return 0;
}