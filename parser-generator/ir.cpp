#include "ir.h"

using namespace std;

string IRBuilder::binOpSymbol(const string &op) const {
    if (op == "PLUS") return "+";
    if (op == "MINUS") return "-";
    if (op == "MULTIPLY") return "*";
    if (op == "DIVIDE") return "/";
    if (op == "MOD") return "%";
    if (op == "EQUAL_EQUAL") return "==";
    if (op == "NOT_EQUAL") return "!=";
    if (op == "GREATER") return ">";
    if (op == "LESS") return "<";
    if (op == "GREATER_EQUAL") return ">=";
    if (op == "LESS_EQUAL") return "<=";
    return op;
}

string IRBuilder::newTemp() { return "t" + to_string(++tempId); }
string IRBuilder::newLabel() { return "L" + to_string(++labelId); }

void IRBuilder::emit(const string &op, const string &a1,
                     const string &a2, const string &res) {
    quads.push_back({op, a1, a2, res});
}

void IRBuilder::dump(ostream &os) const {
    for (const auto &q : quads) {
        if (q.op == "LABEL") {
            os << q.result << ":\n";
        } else if (q.op == "GOTO") {
            os << "    goto " << q.result << "\n";
        } else if (q.op == "IF_FALSE") {
            os << "    ifFalse " << q.arg1 << " goto " << q.result << "\n";
        } else if (q.op == "=") {
            os << "    " << q.result << " = " << q.arg1 << "\n";
        } else {
            os << "    " << q.result << " = " << q.arg1 << " " << binOpSymbol(q.op)
               << " " << q.arg2 << "\n";
        }
    }
}