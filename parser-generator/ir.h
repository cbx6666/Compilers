#pragma once
#include <string>
#include <vector>
#include <ostream>

// 三地址码四元式
struct Quad {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

// 简易 IR 构建器：支持临时变量、标签、发射指令、打印
class IRBuilder {
  private:
    std::vector<Quad> quads;
    int tempId = 0;
    int labelId = 0;

    std::string binOpSymbol(const std::string &op) const;

  public:
    std::string newTemp();
    std::string newLabel();

    void emit(const std::string &op, const std::string &a1,
              const std::string &a2, const std::string &res);

    const std::vector<Quad> &getQuads() const { return quads; }

    void dump(std::ostream &os) const;
};