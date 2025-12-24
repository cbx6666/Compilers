#pragma once
#include "NFA.h"
#include "RegexAST.h"
#include <memory>

using namespace std;

// Thompson构造算法：将正则表达式AST转换为NFA
class ThompsonConstruction {
  private:
    int stateIdCounter;

    int getNextStateId() { return stateIdCounter++; }

  public:
    ThompsonConstruction() : stateIdCounter(0) {}

    // 将AST转换为NFA
    shared_ptr<NFA> build(shared_ptr<ASTNode> ast);

  private:
    // 为不同类型的节点构建NFA
    shared_ptr<NFA> buildChar(shared_ptr<CharNode> node);
    shared_ptr<NFA> buildCharset(shared_ptr<CharsetNode> node);
    shared_ptr<NFA> buildConcat(shared_ptr<ConcatNode> node);
    shared_ptr<NFA> buildUnion(shared_ptr<UnionNode> node);
    shared_ptr<NFA> buildStar(shared_ptr<StarNode> node);
    shared_ptr<NFA> buildPlus(shared_ptr<PlusNode> node);
    shared_ptr<NFA> buildAny(shared_ptr<AnyNode> node);
    shared_ptr<NFA> buildEpsilon(shared_ptr<EpsilonNode> node);
};
