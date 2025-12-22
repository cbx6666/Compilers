# 词法分析器生成器 (Lexer Generator)

一个基于经典编译原理算法的词法分析器生成器，能够根据正则表达式规则自动生成高效的 C++ 词法分析器代码。

## 功能特性

- ✅ **自动生成词法分析器**：根据规则文件自动生成 C++ 词法分析器代码
- ✅ **正则表达式支持**：支持完整的正则表达式语法（字符类、闭包、连接、并等）
- ✅ **经典算法实现**：
  - Thompson 构造算法（正则表达式 → NFA）
  - 子集构造算法（NFA → DFA）
  - DFA 最小化算法（等价类划分）
- ✅ **最长匹配原则**：自动选择最长匹配的 token
- ✅ **IGNORE 规则**：支持忽略空白字符和注释
- ✅ **错误报告**：提供详细的错误位置信息

## 项目结构

```
lexer-generator/
├── main.cpp                 # 主程序入口
├── FileParser.h/cpp         # 规则文件解析器
├── RegexAST.h               # 正则表达式 AST 节点定义
├── RegexParser.h/cpp        # 正则表达式解析器（递归下降）
├── Thompson.h/cpp            # Thompson 构造算法
├── NFA.h/cpp                # NFA 数据结构
├── SubsetConstruction.h/cpp # 子集构造算法（NFA → DFA）
├── DFAMinimizer.h/cpp       # DFA 最小化算法
├── DFA.h                    # DFA 数据结构
├── CodeGenerator.h/cpp      # 代码生成器
├── lexer_rules.txt          # 词法规则文件
├── test_lexer.cpp           # 测试程序
└── generated_lexer.cpp      # 生成的词法分析器（自动生成）
```

## 编译方法

### 编译词法分析器生成器

```bash
g++ -std=c++11 FileParser.cpp RegexParser.cpp NFA.cpp Thompson.cpp SubsetConstruction.cpp DFAMinimizer.cpp CodeGenerator.cpp main.cpp -o lexer_generator.exe
```

### 运行生成器

```bash
./lexer_generator.exe
```

这将读取 `lexer_rules.txt` 并生成 `generated_lexer.cpp`。

### 编译测试程序

```bash
g++ -std=c++11 test_lexer.cpp -o test_lexer.exe
```

### 运行测试

```bash
./test_lexer.exe
```

## 规则文件格式

规则文件 `lexer_rules.txt` 的格式如下：

```
TOKEN_TYPE    REGEX_PATTERN [IGNORE]
```

- `TOKEN_TYPE`：token 类型名称（如 `ID`、`NUMBER` 等）
- `REGEX_PATTERN`：正则表达式模式
- `IGNORE`（可选）：如果规则匹配成功，不返回 token（用于注释、空白等）

### 示例规则文件

```
# 数字
FLOAT_NUMBER    [0-9]+\.[0-9]+
NUMBER          [0-9]+

# 关键字
IF      if
INT     int

# 标识符
ID      [a-zA-Z_][a-zA-Z0-9_]*

# 注释（忽略）
LINE_COMMENT    //.* IGNORE
```

## 支持的正则表达式语法

### 基本操作符

- **字符**：`a`、`b`、`1` 等单个字符
- **连接**：`ab` 表示 a 后跟 b
- **并（或）**：`a|b` 表示 a 或 b
- **Kleene 闭包**：`a*` 表示 0 次或多次 a
- **正闭包**：`a+` 表示 1 次或多次 a
- **任意字符**：`.` 表示除换行符外的任意字符

### 字符类

- **字符集**：`[abc]` 表示 a、b 或 c
- **字符范围**：`[a-z]` 表示 a 到 z 的所有字符
- **取反字符类**：`[^abc]` 表示除 a、b、c 外的所有字符
- **组合**：`[a-zA-Z0-9]` 表示字母和数字

### 转义字符

- `\n`：换行符
- `\t`：制表符
- `\r`：回车符
- `\\`：反斜杠
- `\"`：双引号
- `\+`、`\*`、`\(`、`\)` 等：转义特殊字符

### 示例

```
# 标识符：字母或下划线开头，后跟字母、数字或下划线
ID      [a-zA-Z_][a-zA-Z0-9_]*

# 浮点数：数字.数字
FLOAT_NUMBER    [0-9]+\.[0-9]+

# 字符串字面量：双引号包围的任意字符（除双引号）
STRING_LITERAL  \"[^\"]*\"

# 行注释：// 后跟任意字符（除换行符）
LINE_COMMENT    //.*
```

## 匹配规则

1. **最长匹配原则**：当多个规则都能匹配时，选择匹配长度最长的规则
2. **规则顺序**：当多个规则匹配长度相同时，选择规则文件中先出现的规则
3. **空白字符**：空白字符（空格、制表符、换行符、回车符）在匹配前自动跳过，不作为 token 返回

## 使用示例

### 1. 定义规则文件

创建 `lexer_rules.txt`：

```
NUMBER    [0-9]+
PLUS      \+
ID        [a-zA-Z_][a-zA-Z0-9_]*
```

### 2. 生成词法分析器

```bash
./lexer_generator.exe
```

### 3. 使用生成的词法分析器

在代码中包含生成的词法分析器：

```cpp
#include "generated_lexer.cpp"

int main() {
    string code = "x = 123 + 456";
    Lexer lexer(code);
    
    vector<Token*> tokens = lexer.tokenize();
    for (auto token : tokens) {
        cout << token->toString() << endl;
    }
    
    return 0;
}
```

## 技术实现

### 1. 正则表达式解析

使用**递归下降解析器**将正则表达式字符串解析为抽象语法树（AST）。

### 2. Thompson 构造算法

将正则表达式 AST 转换为非确定有限自动机（NFA）。

### 3. 子集构造算法

将 NFA 转换为确定有限自动机（DFA），使用 epsilon 闭包和状态转换。

### 4. DFA 最小化

使用**等价类划分算法**最小化 DFA，减少状态数量。

### 5. 代码生成

根据最小化的 DFA 生成高效的 C++ 词法分析器代码，使用状态转换表进行匹配。

## 注意事项

1. **空白字符处理**：空白字符在 `nextToken()` 开头自动跳过，不需要在规则文件中定义
2. **转义字符**：在规则文件中，特殊字符需要使用反斜杠转义（如 `\+`、`\*`、`\(` 等）
3. **字符串字面量**：当前版本不支持转义字符（如 `\"`、`\n`），仅支持简单字符串
4. **规则顺序**：关键字规则应放在标识符规则之前，以确保正确匹配
