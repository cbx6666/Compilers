#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

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

class Lexer {
private:
    string text;
    size_t pos;
    int line;
    int column;
    
    int matchDFA0(size_t startPos);
    int matchDFA1(size_t startPos);
    int matchDFA2(size_t startPos);
    int matchDFA3(size_t startPos);
    int matchDFA4(size_t startPos);
    int matchDFA5(size_t startPos);
    int matchDFA6(size_t startPos);
    int matchDFA7(size_t startPos);
    int matchDFA8(size_t startPos);
    int matchDFA9(size_t startPos);
    int matchDFA10(size_t startPos);
    int matchDFA11(size_t startPos);
    int matchDFA12(size_t startPos);
    int matchDFA13(size_t startPos);
    int matchDFA14(size_t startPos);
    int matchDFA15(size_t startPos);
    int matchDFA16(size_t startPos);
    int matchDFA17(size_t startPos);
    int matchDFA18(size_t startPos);
    int matchDFA19(size_t startPos);
    int matchDFA20(size_t startPos);
    int matchDFA21(size_t startPos);
    int matchDFA22(size_t startPos);
    int matchDFA23(size_t startPos);
    int matchDFA24(size_t startPos);
    int matchDFA25(size_t startPos);
    int matchDFA26(size_t startPos);
    int matchDFA27(size_t startPos);
    int matchDFA28(size_t startPos);
    int matchDFA29(size_t startPos);
    int matchDFA30(size_t startPos);
    int matchDFA31(size_t startPos);
    int matchDFA32(size_t startPos);
    int matchDFA33(size_t startPos);
    int matchDFA34(size_t startPos);
    int matchDFA35(size_t startPos);
    int matchDFA36(size_t startPos);
    int matchDFA37(size_t startPos);
    int matchDFA38(size_t startPos);
    
public:
    Lexer(const string& input) : text(input), pos(0), line(1), column(1) {}
    
    Token* nextToken();
    vector<Token*> tokenize();
};

Token* Lexer::nextToken() {
    // 跳过空白字符
    while (pos < text.length() && (text[pos] == ' ' || text[pos] == '\t' || text[pos] == '\n' || text[pos] == '\r')) {
        if (text[pos] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        pos++;
    }
    
    if (pos >= text.length()) {
        return nullptr;
    }
    
    // 尝试匹配每个规则（按文件中的顺序）
    int longestLength = 0;
    string matchedType;
    
    // 规则: FLOAT_NUMBER
    int match0 = matchDFA0(pos);
    if (match0 > longestLength) {
        longestLength = match0;
        matchedType = "FLOAT_NUMBER";
    }
    
    // 规则: NUMBER
    int match1 = matchDFA1(pos);
    if (match1 > longestLength) {
        longestLength = match1;
        matchedType = "NUMBER";
    }
    
    // 规则: STRING_LITERAL
    int match2 = matchDFA2(pos);
    if (match2 > longestLength) {
        longestLength = match2;
        matchedType = "STRING_LITERAL";
    }
    
    // 规则: IF
    int match3 = matchDFA3(pos);
    if (match3 > longestLength) {
        longestLength = match3;
        matchedType = "IF";
    }
    
    // 规则: ELSE
    int match4 = matchDFA4(pos);
    if (match4 > longestLength) {
        longestLength = match4;
        matchedType = "ELSE";
    }
    
    // 规则: FOR
    int match5 = matchDFA5(pos);
    if (match5 > longestLength) {
        longestLength = match5;
        matchedType = "FOR";
    }
    
    // 规则: WHILE
    int match6 = matchDFA6(pos);
    if (match6 > longestLength) {
        longestLength = match6;
        matchedType = "WHILE";
    }
    
    // 规则: DO
    int match7 = matchDFA7(pos);
    if (match7 > longestLength) {
        longestLength = match7;
        matchedType = "DO";
    }
    
    // 规则: BREAK
    int match8 = matchDFA8(pos);
    if (match8 > longestLength) {
        longestLength = match8;
        matchedType = "BREAK";
    }
    
    // 规则: CONTINUE
    int match9 = matchDFA9(pos);
    if (match9 > longestLength) {
        longestLength = match9;
        matchedType = "CONTINUE";
    }
    
    // 规则: RETURN
    int match10 = matchDFA10(pos);
    if (match10 > longestLength) {
        longestLength = match10;
        matchedType = "RETURN";
    }
    
    // 规则: VOID
    int match11 = matchDFA11(pos);
    if (match11 > longestLength) {
        longestLength = match11;
        matchedType = "VOID";
    }
    
    // 规则: INT
    int match12 = matchDFA12(pos);
    if (match12 > longestLength) {
        longestLength = match12;
        matchedType = "INT";
    }
    
    // 规则: FLOAT
    int match13 = matchDFA13(pos);
    if (match13 > longestLength) {
        longestLength = match13;
        matchedType = "FLOAT";
    }
    
    // 规则: CHAR
    int match14 = matchDFA14(pos);
    if (match14 > longestLength) {
        longestLength = match14;
        matchedType = "CHAR";
    }
    
    // 规则: STRING
    int match15 = matchDFA15(pos);
    if (match15 > longestLength) {
        longestLength = match15;
        matchedType = "STRING";
    }
    
    // 规则: ID
    int match16 = matchDFA16(pos);
    if (match16 > longestLength) {
        longestLength = match16;
        matchedType = "ID";
    }
    
    // 规则: NOT_EQUAL
    int match17 = matchDFA17(pos);
    if (match17 > longestLength) {
        longestLength = match17;
        matchedType = "NOT_EQUAL";
    }
    
    // 规则: EQUAL_EQUAL
    int match18 = matchDFA18(pos);
    if (match18 > longestLength) {
        longestLength = match18;
        matchedType = "EQUAL_EQUAL";
    }
    
    // 规则: GREATER_EQUAL
    int match19 = matchDFA19(pos);
    if (match19 > longestLength) {
        longestLength = match19;
        matchedType = "GREATER_EQUAL";
    }
    
    // 规则: LESS_EQUAL
    int match20 = matchDFA20(pos);
    if (match20 > longestLength) {
        longestLength = match20;
        matchedType = "LESS_EQUAL";
    }
    
    // 规则: EQUAL
    int match21 = matchDFA21(pos);
    if (match21 > longestLength) {
        longestLength = match21;
        matchedType = "EQUAL";
    }
    
    // 规则: GREATER
    int match22 = matchDFA22(pos);
    if (match22 > longestLength) {
        longestLength = match22;
        matchedType = "GREATER";
    }
    
    // 规则: LESS
    int match23 = matchDFA23(pos);
    if (match23 > longestLength) {
        longestLength = match23;
        matchedType = "LESS";
    }
    
    // 规则: PLUS
    int match24 = matchDFA24(pos);
    if (match24 > longestLength) {
        longestLength = match24;
        matchedType = "PLUS";
    }
    
    // 规则: MINUS
    int match25 = matchDFA25(pos);
    if (match25 > longestLength) {
        longestLength = match25;
        matchedType = "MINUS";
    }
    
    // 规则: MULTIPLY
    int match26 = matchDFA26(pos);
    if (match26 > longestLength) {
        longestLength = match26;
        matchedType = "MULTIPLY";
    }
    
    // 规则: DIVIDE
    int match27 = matchDFA27(pos);
    if (match27 > longestLength) {
        longestLength = match27;
        matchedType = "DIVIDE";
    }
    
    // 规则: MOD
    int match28 = matchDFA28(pos);
    if (match28 > longestLength) {
        longestLength = match28;
        matchedType = "MOD";
    }
    
    // 规则: COMMA
    int match29 = matchDFA29(pos);
    if (match29 > longestLength) {
        longestLength = match29;
        matchedType = "COMMA";
    }
    
    // 规则: SEMICOLON
    int match30 = matchDFA30(pos);
    if (match30 > longestLength) {
        longestLength = match30;
        matchedType = "SEMICOLON";
    }
    
    // 规则: COLON
    int match31 = matchDFA31(pos);
    if (match31 > longestLength) {
        longestLength = match31;
        matchedType = "COLON";
    }
    
    // 规则: LPAREN
    int match32 = matchDFA32(pos);
    if (match32 > longestLength) {
        longestLength = match32;
        matchedType = "LPAREN";
    }
    
    // 规则: RPAREN
    int match33 = matchDFA33(pos);
    if (match33 > longestLength) {
        longestLength = match33;
        matchedType = "RPAREN";
    }
    
    // 规则: LBRACE
    int match34 = matchDFA34(pos);
    if (match34 > longestLength) {
        longestLength = match34;
        matchedType = "LBRACE";
    }
    
    // 规则: RBRACE
    int match35 = matchDFA35(pos);
    if (match35 > longestLength) {
        longestLength = match35;
        matchedType = "RBRACE";
    }
    
    // 规则: LBRACKET
    int match36 = matchDFA36(pos);
    if (match36 > longestLength) {
        longestLength = match36;
        matchedType = "LBRACKET";
    }
    
    // 规则: RBRACKET
    int match37 = matchDFA37(pos);
    if (match37 > longestLength) {
        longestLength = match37;
        matchedType = "RBRACKET";
    }
    
    // 规则: LINE_COMMENT (IGNORE)
    int match38 = matchDFA38(pos);
    if (match38 > 0) {
        pos += match38;
        column += match38;
        return nextToken();  // 继续匹配下一个token
    }
    
    if (longestLength > 0) {
        string value = text.substr(pos, longestLength);
        Token* token = new Token(matchedType, value, line, column);
        pos += longestLength;
        column += longestLength;
        return token;
    }
    
    // 错误：无法识别的字符
    throw runtime_error("Unexpected character '" + string(1, text[pos]) + "' at line " + to_string(line) + ", column " + to_string(column));
}

vector<Token*> Lexer::tokenize() {
    vector<Token*> tokens;
    while (pos < text.length()) {
        Token* token = nextToken();
        if (token) {
            tokens.push_back(token);
        } else {
            break;
        }
    }
    return tokens;
}

int Lexer::matchDFA0(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[4] = {false, false, false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[4][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][48] = 1;
    transitions[0][49] = 1;
    transitions[0][50] = 1;
    transitions[0][51] = 1;
    transitions[0][52] = 1;
    transitions[0][53] = 1;
    transitions[0][54] = 1;
    transitions[0][55] = 1;
    transitions[0][56] = 1;
    transitions[0][57] = 1;
    transitions[1][46] = 2;
    transitions[1][48] = 1;
    transitions[1][49] = 1;
    transitions[1][50] = 1;
    transitions[1][51] = 1;
    transitions[1][52] = 1;
    transitions[1][53] = 1;
    transitions[1][54] = 1;
    transitions[1][55] = 1;
    transitions[1][56] = 1;
    transitions[1][57] = 1;
    transitions[2][48] = 3;
    transitions[2][49] = 3;
    transitions[2][50] = 3;
    transitions[2][51] = 3;
    transitions[2][52] = 3;
    transitions[2][53] = 3;
    transitions[2][54] = 3;
    transitions[2][55] = 3;
    transitions[2][56] = 3;
    transitions[2][57] = 3;
    transitions[3][48] = 3;
    transitions[3][49] = 3;
    transitions[3][50] = 3;
    transitions[3][51] = 3;
    transitions[3][52] = 3;
    transitions[3][53] = 3;
    transitions[3][54] = 3;
    transitions[3][55] = 3;
    transitions[3][56] = 3;
    transitions[3][57] = 3;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA1(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][48] = 1;
    transitions[0][49] = 1;
    transitions[0][50] = 1;
    transitions[0][51] = 1;
    transitions[0][52] = 1;
    transitions[0][53] = 1;
    transitions[0][54] = 1;
    transitions[0][55] = 1;
    transitions[0][56] = 1;
    transitions[0][57] = 1;
    transitions[1][48] = 1;
    transitions[1][49] = 1;
    transitions[1][50] = 1;
    transitions[1][51] = 1;
    transitions[1][52] = 1;
    transitions[1][53] = 1;
    transitions[1][54] = 1;
    transitions[1][55] = 1;
    transitions[1][56] = 1;
    transitions[1][57] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA2(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][34] = 2;
    transitions[2][128] = 2;
    transitions[2][129] = 2;
    transitions[2][130] = 2;
    transitions[2][131] = 2;
    transitions[2][132] = 2;
    transitions[2][133] = 2;
    transitions[2][134] = 2;
    transitions[2][135] = 2;
    transitions[2][136] = 2;
    transitions[2][137] = 2;
    transitions[2][138] = 2;
    transitions[2][139] = 2;
    transitions[2][140] = 2;
    transitions[2][141] = 2;
    transitions[2][142] = 2;
    transitions[2][143] = 2;
    transitions[2][144] = 2;
    transitions[2][145] = 2;
    transitions[2][146] = 2;
    transitions[2][147] = 2;
    transitions[2][148] = 2;
    transitions[2][149] = 2;
    transitions[2][150] = 2;
    transitions[2][151] = 2;
    transitions[2][152] = 2;
    transitions[2][153] = 2;
    transitions[2][154] = 2;
    transitions[2][155] = 2;
    transitions[2][156] = 2;
    transitions[2][157] = 2;
    transitions[2][158] = 2;
    transitions[2][159] = 2;
    transitions[2][160] = 2;
    transitions[2][161] = 2;
    transitions[2][162] = 2;
    transitions[2][163] = 2;
    transitions[2][164] = 2;
    transitions[2][165] = 2;
    transitions[2][166] = 2;
    transitions[2][167] = 2;
    transitions[2][168] = 2;
    transitions[2][169] = 2;
    transitions[2][170] = 2;
    transitions[2][171] = 2;
    transitions[2][172] = 2;
    transitions[2][173] = 2;
    transitions[2][174] = 2;
    transitions[2][175] = 2;
    transitions[2][176] = 2;
    transitions[2][177] = 2;
    transitions[2][178] = 2;
    transitions[2][179] = 2;
    transitions[2][180] = 2;
    transitions[2][181] = 2;
    transitions[2][182] = 2;
    transitions[2][183] = 2;
    transitions[2][184] = 2;
    transitions[2][185] = 2;
    transitions[2][186] = 2;
    transitions[2][187] = 2;
    transitions[2][188] = 2;
    transitions[2][189] = 2;
    transitions[2][190] = 2;
    transitions[2][191] = 2;
    transitions[2][192] = 2;
    transitions[2][193] = 2;
    transitions[2][194] = 2;
    transitions[2][195] = 2;
    transitions[2][196] = 2;
    transitions[2][197] = 2;
    transitions[2][198] = 2;
    transitions[2][199] = 2;
    transitions[2][200] = 2;
    transitions[2][201] = 2;
    transitions[2][202] = 2;
    transitions[2][203] = 2;
    transitions[2][204] = 2;
    transitions[2][205] = 2;
    transitions[2][206] = 2;
    transitions[2][207] = 2;
    transitions[2][208] = 2;
    transitions[2][209] = 2;
    transitions[2][210] = 2;
    transitions[2][211] = 2;
    transitions[2][212] = 2;
    transitions[2][213] = 2;
    transitions[2][214] = 2;
    transitions[2][215] = 2;
    transitions[2][216] = 2;
    transitions[2][217] = 2;
    transitions[2][218] = 2;
    transitions[2][219] = 2;
    transitions[2][220] = 2;
    transitions[2][221] = 2;
    transitions[2][222] = 2;
    transitions[2][223] = 2;
    transitions[2][224] = 2;
    transitions[2][225] = 2;
    transitions[2][226] = 2;
    transitions[2][227] = 2;
    transitions[2][228] = 2;
    transitions[2][229] = 2;
    transitions[2][230] = 2;
    transitions[2][231] = 2;
    transitions[2][232] = 2;
    transitions[2][233] = 2;
    transitions[2][234] = 2;
    transitions[2][235] = 2;
    transitions[2][236] = 2;
    transitions[2][237] = 2;
    transitions[2][238] = 2;
    transitions[2][239] = 2;
    transitions[2][240] = 2;
    transitions[2][241] = 2;
    transitions[2][242] = 2;
    transitions[2][243] = 2;
    transitions[2][244] = 2;
    transitions[2][245] = 2;
    transitions[2][246] = 2;
    transitions[2][247] = 2;
    transitions[2][248] = 2;
    transitions[2][249] = 2;
    transitions[2][250] = 2;
    transitions[2][251] = 2;
    transitions[2][252] = 2;
    transitions[2][253] = 2;
    transitions[2][254] = 2;
    transitions[2][255] = 2;
    transitions[2][1] = 2;
    transitions[2][2] = 2;
    transitions[2][3] = 2;
    transitions[2][4] = 2;
    transitions[2][5] = 2;
    transitions[2][6] = 2;
    transitions[2][7] = 2;
    transitions[2][8] = 2;
    transitions[2][9] = 2;
    transitions[2][11] = 2;
    transitions[2][12] = 2;
    transitions[2][13] = 2;
    transitions[2][14] = 2;
    transitions[2][15] = 2;
    transitions[2][16] = 2;
    transitions[2][17] = 2;
    transitions[2][18] = 2;
    transitions[2][19] = 2;
    transitions[2][20] = 2;
    transitions[2][21] = 2;
    transitions[2][22] = 2;
    transitions[2][23] = 2;
    transitions[2][24] = 2;
    transitions[2][25] = 2;
    transitions[2][26] = 2;
    transitions[2][27] = 2;
    transitions[2][28] = 2;
    transitions[2][29] = 2;
    transitions[2][30] = 2;
    transitions[2][31] = 2;
    transitions[2][32] = 2;
    transitions[2][33] = 2;
    transitions[2][34] = 0;
    transitions[2][35] = 2;
    transitions[2][36] = 2;
    transitions[2][37] = 2;
    transitions[2][38] = 2;
    transitions[2][39] = 2;
    transitions[2][40] = 2;
    transitions[2][41] = 2;
    transitions[2][42] = 2;
    transitions[2][43] = 2;
    transitions[2][44] = 2;
    transitions[2][45] = 2;
    transitions[2][46] = 2;
    transitions[2][47] = 2;
    transitions[2][48] = 2;
    transitions[2][49] = 2;
    transitions[2][50] = 2;
    transitions[2][51] = 2;
    transitions[2][52] = 2;
    transitions[2][53] = 2;
    transitions[2][54] = 2;
    transitions[2][55] = 2;
    transitions[2][56] = 2;
    transitions[2][57] = 2;
    transitions[2][58] = 2;
    transitions[2][59] = 2;
    transitions[2][60] = 2;
    transitions[2][61] = 2;
    transitions[2][62] = 2;
    transitions[2][63] = 2;
    transitions[2][64] = 2;
    transitions[2][65] = 2;
    transitions[2][66] = 2;
    transitions[2][67] = 2;
    transitions[2][68] = 2;
    transitions[2][69] = 2;
    transitions[2][70] = 2;
    transitions[2][71] = 2;
    transitions[2][72] = 2;
    transitions[2][73] = 2;
    transitions[2][74] = 2;
    transitions[2][75] = 2;
    transitions[2][76] = 2;
    transitions[2][77] = 2;
    transitions[2][78] = 2;
    transitions[2][79] = 2;
    transitions[2][80] = 2;
    transitions[2][81] = 2;
    transitions[2][82] = 2;
    transitions[2][83] = 2;
    transitions[2][84] = 2;
    transitions[2][85] = 2;
    transitions[2][86] = 2;
    transitions[2][87] = 2;
    transitions[2][88] = 2;
    transitions[2][89] = 2;
    transitions[2][90] = 2;
    transitions[2][91] = 2;
    transitions[2][92] = 2;
    transitions[2][93] = 2;
    transitions[2][94] = 2;
    transitions[2][95] = 2;
    transitions[2][96] = 2;
    transitions[2][97] = 2;
    transitions[2][98] = 2;
    transitions[2][99] = 2;
    transitions[2][100] = 2;
    transitions[2][101] = 2;
    transitions[2][102] = 2;
    transitions[2][103] = 2;
    transitions[2][104] = 2;
    transitions[2][105] = 2;
    transitions[2][106] = 2;
    transitions[2][107] = 2;
    transitions[2][108] = 2;
    transitions[2][109] = 2;
    transitions[2][110] = 2;
    transitions[2][111] = 2;
    transitions[2][112] = 2;
    transitions[2][113] = 2;
    transitions[2][114] = 2;
    transitions[2][115] = 2;
    transitions[2][116] = 2;
    transitions[2][117] = 2;
    transitions[2][118] = 2;
    transitions[2][119] = 2;
    transitions[2][120] = 2;
    transitions[2][121] = 2;
    transitions[2][122] = 2;
    transitions[2][123] = 2;
    transitions[2][124] = 2;
    transitions[2][125] = 2;
    transitions[2][126] = 2;
    transitions[2][127] = 2;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA3(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][105] = 2;
    transitions[2][102] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA4(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[5] = {false, false, true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[5][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][108] = 4;
    transitions[1][101] = 0;
    transitions[3][101] = 2;
    transitions[4][115] = 3;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA5(size_t startPos) {
    int state = 3;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[4] = {false, false, true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[4][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][114] = 2;
    transitions[1][111] = 0;
    transitions[3][102] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA6(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[6] = {true, false, false, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[6][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][119] = 4;
    transitions[2][108] = 5;
    transitions[3][105] = 2;
    transitions[4][104] = 3;
    transitions[5][101] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA7(size_t startPos) {
    int state = 2;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {false, true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][111] = 1;
    transitions[2][100] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA8(size_t startPos) {
    int state = 2;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[6] = {true, false, false, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[6][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][114] = 5;
    transitions[2][98] = 1;
    transitions[3][97] = 4;
    transitions[4][107] = 0;
    transitions[5][101] = 3;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA9(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[9] = {false, false, false, false, true, false, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[9][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][99] = 5;
    transitions[1][117] = 7;
    transitions[2][116] = 6;
    transitions[3][110] = 1;
    transitions[5][111] = 8;
    transitions[6][105] = 3;
    transitions[7][101] = 4;
    transitions[8][110] = 2;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA10(size_t startPos) {
    int state = 6;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[7] = {false, false, true, false, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[7][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][110] = 2;
    transitions[1][101] = 4;
    transitions[3][114] = 0;
    transitions[4][116] = 5;
    transitions[5][117] = 3;
    transitions[6][114] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA11(size_t startPos) {
    int state = 2;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[5] = {false, true, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[5][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][111] = 3;
    transitions[2][118] = 0;
    transitions[3][105] = 4;
    transitions[4][100] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA12(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[4] = {true, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[4][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][105] = 3;
    transitions[2][116] = 0;
    transitions[3][110] = 2;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA13(size_t startPos) {
    int state = 4;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[6] = {false, false, true, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[6][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][97] = 1;
    transitions[1][116] = 2;
    transitions[3][108] = 5;
    transitions[4][102] = 3;
    transitions[5][111] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA14(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[5] = {false, false, true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[5][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][104] = 3;
    transitions[1][99] = 0;
    transitions[3][97] = 4;
    transitions[4][114] = 2;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA15(size_t startPos) {
    int state = 2;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[7] = {true, false, false, false, false, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[7][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][116] = 5;
    transitions[2][115] = 1;
    transitions[3][105] = 6;
    transitions[4][103] = 0;
    transitions[5][114] = 3;
    transitions[6][110] = 4;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA16(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][65] = 1;
    transitions[0][66] = 1;
    transitions[0][67] = 1;
    transitions[0][68] = 1;
    transitions[0][69] = 1;
    transitions[0][70] = 1;
    transitions[0][71] = 1;
    transitions[0][72] = 1;
    transitions[0][73] = 1;
    transitions[0][74] = 1;
    transitions[0][75] = 1;
    transitions[0][76] = 1;
    transitions[0][77] = 1;
    transitions[0][78] = 1;
    transitions[0][79] = 1;
    transitions[0][80] = 1;
    transitions[0][81] = 1;
    transitions[0][82] = 1;
    transitions[0][83] = 1;
    transitions[0][84] = 1;
    transitions[0][85] = 1;
    transitions[0][86] = 1;
    transitions[0][87] = 1;
    transitions[0][88] = 1;
    transitions[0][89] = 1;
    transitions[0][90] = 1;
    transitions[0][95] = 1;
    transitions[0][97] = 1;
    transitions[0][98] = 1;
    transitions[0][99] = 1;
    transitions[0][100] = 1;
    transitions[0][101] = 1;
    transitions[0][102] = 1;
    transitions[0][103] = 1;
    transitions[0][104] = 1;
    transitions[0][105] = 1;
    transitions[0][106] = 1;
    transitions[0][107] = 1;
    transitions[0][108] = 1;
    transitions[0][109] = 1;
    transitions[0][110] = 1;
    transitions[0][111] = 1;
    transitions[0][112] = 1;
    transitions[0][113] = 1;
    transitions[0][114] = 1;
    transitions[0][115] = 1;
    transitions[0][116] = 1;
    transitions[0][117] = 1;
    transitions[0][118] = 1;
    transitions[0][119] = 1;
    transitions[0][120] = 1;
    transitions[0][121] = 1;
    transitions[0][122] = 1;
    transitions[1][48] = 1;
    transitions[1][49] = 1;
    transitions[1][50] = 1;
    transitions[1][51] = 1;
    transitions[1][52] = 1;
    transitions[1][53] = 1;
    transitions[1][54] = 1;
    transitions[1][55] = 1;
    transitions[1][56] = 1;
    transitions[1][57] = 1;
    transitions[1][65] = 1;
    transitions[1][66] = 1;
    transitions[1][67] = 1;
    transitions[1][68] = 1;
    transitions[1][69] = 1;
    transitions[1][70] = 1;
    transitions[1][71] = 1;
    transitions[1][72] = 1;
    transitions[1][73] = 1;
    transitions[1][74] = 1;
    transitions[1][75] = 1;
    transitions[1][76] = 1;
    transitions[1][77] = 1;
    transitions[1][78] = 1;
    transitions[1][79] = 1;
    transitions[1][80] = 1;
    transitions[1][81] = 1;
    transitions[1][82] = 1;
    transitions[1][83] = 1;
    transitions[1][84] = 1;
    transitions[1][85] = 1;
    transitions[1][86] = 1;
    transitions[1][87] = 1;
    transitions[1][88] = 1;
    transitions[1][89] = 1;
    transitions[1][90] = 1;
    transitions[1][95] = 1;
    transitions[1][97] = 1;
    transitions[1][98] = 1;
    transitions[1][99] = 1;
    transitions[1][100] = 1;
    transitions[1][101] = 1;
    transitions[1][102] = 1;
    transitions[1][103] = 1;
    transitions[1][104] = 1;
    transitions[1][105] = 1;
    transitions[1][106] = 1;
    transitions[1][107] = 1;
    transitions[1][108] = 1;
    transitions[1][109] = 1;
    transitions[1][110] = 1;
    transitions[1][111] = 1;
    transitions[1][112] = 1;
    transitions[1][113] = 1;
    transitions[1][114] = 1;
    transitions[1][115] = 1;
    transitions[1][116] = 1;
    transitions[1][117] = 1;
    transitions[1][118] = 1;
    transitions[1][119] = 1;
    transitions[1][120] = 1;
    transitions[1][121] = 1;
    transitions[1][122] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA17(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {false, false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][61] = 2;
    transitions[1][33] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA18(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {false, false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][61] = 2;
    transitions[1][61] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA19(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][62] = 2;
    transitions[2][61] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA20(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {true, false, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][60] = 2;
    transitions[2][61] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA21(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][61] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA22(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][62] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA23(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][60] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA24(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][43] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA25(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][45] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA26(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][42] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA27(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][47] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA28(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][37] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA29(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][44] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA30(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][59] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA31(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][58] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA32(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][40] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA33(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][41] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA34(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][123] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA35(size_t startPos) {
    int state = 1;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {true, false};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[1][125] = 0;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA36(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][91] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA37(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[2] = {false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[2][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][93] = 1;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

int Lexer::matchDFA38(size_t startPos) {
    int state = 0;
    size_t currentPos = startPos;
    size_t lastAcceptingPos = string::npos;
    
    // 接受状态集合
    bool accepting[3] = {false, false, true};
    
    // 状态转换表: transitions[state][char] = nextState
    int transitions[3][256];
    // 初始化为-1（无转换）
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            transitions[i][j] = -1;
        }
    }
    
    transitions[0][47] = 1;
    transitions[1][47] = 2;
    transitions[2][128] = 2;
    transitions[2][129] = 2;
    transitions[2][130] = 2;
    transitions[2][131] = 2;
    transitions[2][132] = 2;
    transitions[2][133] = 2;
    transitions[2][134] = 2;
    transitions[2][135] = 2;
    transitions[2][136] = 2;
    transitions[2][137] = 2;
    transitions[2][138] = 2;
    transitions[2][139] = 2;
    transitions[2][140] = 2;
    transitions[2][141] = 2;
    transitions[2][142] = 2;
    transitions[2][143] = 2;
    transitions[2][144] = 2;
    transitions[2][145] = 2;
    transitions[2][146] = 2;
    transitions[2][147] = 2;
    transitions[2][148] = 2;
    transitions[2][149] = 2;
    transitions[2][150] = 2;
    transitions[2][151] = 2;
    transitions[2][152] = 2;
    transitions[2][153] = 2;
    transitions[2][154] = 2;
    transitions[2][155] = 2;
    transitions[2][156] = 2;
    transitions[2][157] = 2;
    transitions[2][158] = 2;
    transitions[2][159] = 2;
    transitions[2][160] = 2;
    transitions[2][161] = 2;
    transitions[2][162] = 2;
    transitions[2][163] = 2;
    transitions[2][164] = 2;
    transitions[2][165] = 2;
    transitions[2][166] = 2;
    transitions[2][167] = 2;
    transitions[2][168] = 2;
    transitions[2][169] = 2;
    transitions[2][170] = 2;
    transitions[2][171] = 2;
    transitions[2][172] = 2;
    transitions[2][173] = 2;
    transitions[2][174] = 2;
    transitions[2][175] = 2;
    transitions[2][176] = 2;
    transitions[2][177] = 2;
    transitions[2][178] = 2;
    transitions[2][179] = 2;
    transitions[2][180] = 2;
    transitions[2][181] = 2;
    transitions[2][182] = 2;
    transitions[2][183] = 2;
    transitions[2][184] = 2;
    transitions[2][185] = 2;
    transitions[2][186] = 2;
    transitions[2][187] = 2;
    transitions[2][188] = 2;
    transitions[2][189] = 2;
    transitions[2][190] = 2;
    transitions[2][191] = 2;
    transitions[2][192] = 2;
    transitions[2][193] = 2;
    transitions[2][194] = 2;
    transitions[2][195] = 2;
    transitions[2][196] = 2;
    transitions[2][197] = 2;
    transitions[2][198] = 2;
    transitions[2][199] = 2;
    transitions[2][200] = 2;
    transitions[2][201] = 2;
    transitions[2][202] = 2;
    transitions[2][203] = 2;
    transitions[2][204] = 2;
    transitions[2][205] = 2;
    transitions[2][206] = 2;
    transitions[2][207] = 2;
    transitions[2][208] = 2;
    transitions[2][209] = 2;
    transitions[2][210] = 2;
    transitions[2][211] = 2;
    transitions[2][212] = 2;
    transitions[2][213] = 2;
    transitions[2][214] = 2;
    transitions[2][215] = 2;
    transitions[2][216] = 2;
    transitions[2][217] = 2;
    transitions[2][218] = 2;
    transitions[2][219] = 2;
    transitions[2][220] = 2;
    transitions[2][221] = 2;
    transitions[2][222] = 2;
    transitions[2][223] = 2;
    transitions[2][224] = 2;
    transitions[2][225] = 2;
    transitions[2][226] = 2;
    transitions[2][227] = 2;
    transitions[2][228] = 2;
    transitions[2][229] = 2;
    transitions[2][230] = 2;
    transitions[2][231] = 2;
    transitions[2][232] = 2;
    transitions[2][233] = 2;
    transitions[2][234] = 2;
    transitions[2][235] = 2;
    transitions[2][236] = 2;
    transitions[2][237] = 2;
    transitions[2][238] = 2;
    transitions[2][239] = 2;
    transitions[2][240] = 2;
    transitions[2][241] = 2;
    transitions[2][242] = 2;
    transitions[2][243] = 2;
    transitions[2][244] = 2;
    transitions[2][245] = 2;
    transitions[2][246] = 2;
    transitions[2][247] = 2;
    transitions[2][248] = 2;
    transitions[2][249] = 2;
    transitions[2][250] = 2;
    transitions[2][251] = 2;
    transitions[2][252] = 2;
    transitions[2][253] = 2;
    transitions[2][254] = 2;
    transitions[2][255] = 2;
    transitions[2][1] = 2;
    transitions[2][2] = 2;
    transitions[2][3] = 2;
    transitions[2][4] = 2;
    transitions[2][5] = 2;
    transitions[2][6] = 2;
    transitions[2][7] = 2;
    transitions[2][8] = 2;
    transitions[2][9] = 2;
    transitions[2][11] = 2;
    transitions[2][12] = 2;
    transitions[2][13] = 2;
    transitions[2][14] = 2;
    transitions[2][15] = 2;
    transitions[2][16] = 2;
    transitions[2][17] = 2;
    transitions[2][18] = 2;
    transitions[2][19] = 2;
    transitions[2][20] = 2;
    transitions[2][21] = 2;
    transitions[2][22] = 2;
    transitions[2][23] = 2;
    transitions[2][24] = 2;
    transitions[2][25] = 2;
    transitions[2][26] = 2;
    transitions[2][27] = 2;
    transitions[2][28] = 2;
    transitions[2][29] = 2;
    transitions[2][30] = 2;
    transitions[2][31] = 2;
    transitions[2][32] = 2;
    transitions[2][33] = 2;
    transitions[2][34] = 2;
    transitions[2][35] = 2;
    transitions[2][36] = 2;
    transitions[2][37] = 2;
    transitions[2][38] = 2;
    transitions[2][39] = 2;
    transitions[2][40] = 2;
    transitions[2][41] = 2;
    transitions[2][42] = 2;
    transitions[2][43] = 2;
    transitions[2][44] = 2;
    transitions[2][45] = 2;
    transitions[2][46] = 2;
    transitions[2][47] = 2;
    transitions[2][48] = 2;
    transitions[2][49] = 2;
    transitions[2][50] = 2;
    transitions[2][51] = 2;
    transitions[2][52] = 2;
    transitions[2][53] = 2;
    transitions[2][54] = 2;
    transitions[2][55] = 2;
    transitions[2][56] = 2;
    transitions[2][57] = 2;
    transitions[2][58] = 2;
    transitions[2][59] = 2;
    transitions[2][60] = 2;
    transitions[2][61] = 2;
    transitions[2][62] = 2;
    transitions[2][63] = 2;
    transitions[2][64] = 2;
    transitions[2][65] = 2;
    transitions[2][66] = 2;
    transitions[2][67] = 2;
    transitions[2][68] = 2;
    transitions[2][69] = 2;
    transitions[2][70] = 2;
    transitions[2][71] = 2;
    transitions[2][72] = 2;
    transitions[2][73] = 2;
    transitions[2][74] = 2;
    transitions[2][75] = 2;
    transitions[2][76] = 2;
    transitions[2][77] = 2;
    transitions[2][78] = 2;
    transitions[2][79] = 2;
    transitions[2][80] = 2;
    transitions[2][81] = 2;
    transitions[2][82] = 2;
    transitions[2][83] = 2;
    transitions[2][84] = 2;
    transitions[2][85] = 2;
    transitions[2][86] = 2;
    transitions[2][87] = 2;
    transitions[2][88] = 2;
    transitions[2][89] = 2;
    transitions[2][90] = 2;
    transitions[2][91] = 2;
    transitions[2][92] = 2;
    transitions[2][93] = 2;
    transitions[2][94] = 2;
    transitions[2][95] = 2;
    transitions[2][96] = 2;
    transitions[2][97] = 2;
    transitions[2][98] = 2;
    transitions[2][99] = 2;
    transitions[2][100] = 2;
    transitions[2][101] = 2;
    transitions[2][102] = 2;
    transitions[2][103] = 2;
    transitions[2][104] = 2;
    transitions[2][105] = 2;
    transitions[2][106] = 2;
    transitions[2][107] = 2;
    transitions[2][108] = 2;
    transitions[2][109] = 2;
    transitions[2][110] = 2;
    transitions[2][111] = 2;
    transitions[2][112] = 2;
    transitions[2][113] = 2;
    transitions[2][114] = 2;
    transitions[2][115] = 2;
    transitions[2][116] = 2;
    transitions[2][117] = 2;
    transitions[2][118] = 2;
    transitions[2][119] = 2;
    transitions[2][120] = 2;
    transitions[2][121] = 2;
    transitions[2][122] = 2;
    transitions[2][123] = 2;
    transitions[2][124] = 2;
    transitions[2][125] = 2;
    transitions[2][126] = 2;
    transitions[2][127] = 2;
    
    // 执行DFA匹配
    while (currentPos < text.length()) {
        unsigned char ch = static_cast<unsigned char>(text[currentPos]);
        int nextState = transitions[state][ch];
        if (nextState == -1) {
            break;
        }
        state = nextState;
        currentPos++;
        if (accepting[state]) {
            lastAcceptingPos = currentPos;
        }
    }
    
    if (lastAcceptingPos != string::npos) {
        return static_cast<int>(lastAcceptingPos - startPos);
    }
    return 0;
}

