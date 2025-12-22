#include "Thompson.h"
#include <set>
#include <stdexcept>

using namespace std;

shared_ptr<NFA> ThompsonConstruction::build(shared_ptr<ASTNode> ast) {
  if (!ast) {
    throw runtime_error("AST节点为空");
  }

  // 根据节点类型调用相应的构建函数
  switch (ast->type) {
  case NodeType::CHAR: {
    auto charNode = dynamic_pointer_cast<CharNode>(ast);
    return buildChar(charNode);
  }
  case NodeType::CHARSET: {
    auto charsetNode = dynamic_pointer_cast<CharsetNode>(ast);
    return buildCharset(charsetNode);
  }
  case NodeType::CONCAT: {
    auto concatNode = dynamic_pointer_cast<ConcatNode>(ast);
    return buildConcat(concatNode);
  }
  case NodeType::UNION: {
    auto unionNode = dynamic_pointer_cast<UnionNode>(ast);
    return buildUnion(unionNode);
  }
  case NodeType::STAR: {
    auto starNode = dynamic_pointer_cast<StarNode>(ast);
    return buildStar(starNode);
  }
  case NodeType::PLUS: {
    auto plusNode = dynamic_pointer_cast<PlusNode>(ast);
    return buildPlus(plusNode);
  }
  case NodeType::ANY: {
    auto anyNode = dynamic_pointer_cast<AnyNode>(ast);
    return buildAny(anyNode);
  }
  case NodeType::EPSILON: {
    auto epsilonNode = dynamic_pointer_cast<EpsilonNode>(ast);
    return buildEpsilon(epsilonNode);
  }
  default:
    throw runtime_error("未知的AST节点类型");
  }
}

// 单个字符的NFA
shared_ptr<NFA> ThompsonConstruction::buildChar(shared_ptr<CharNode> node) {
  auto start = make_shared<NFAState>(getNextStateId());
  auto accept = make_shared<NFAState>(getNextStateId());

  start->addTransition(node->ch, accept);

  return make_shared<NFA>(start, accept);
}

// 字符类的NFA：转换为多个字符的并
shared_ptr<NFA>
ThompsonConstruction::buildCharset(shared_ptr<CharsetNode> node) {
  auto start = make_shared<NFAState>(getNextStateId());
  auto accept = make_shared<NFAState>(getNextStateId());

  if (node->negated) {
    // 取反字符类 [^...]：匹配所有不在 chars 中的字符（除了换行符）
    set<char> excludedChars(node->chars.begin(), node->chars.end());
    for (int i = 0; i < 256; i++) {
      char ch = static_cast<char>(i);
      if (ch != '\n' && excludedChars.find(ch) == excludedChars.end()) {
        start->addTransition(ch, accept);
      }
    }
  } else {
    // 普通字符类 [...]：匹配 chars 中的任意字符
    if (node->chars.empty()) {
      // 空字符类，返回epsilon
      start->addEpsilonTransition(accept);
    } else {
      // 为每个字符添加转换
      for (char ch : node->chars) {
        start->addTransition(ch, accept);
      }
    }
  }

  return make_shared<NFA>(start, accept);
}

// 连接的NFA：NFA1 · NFA2
shared_ptr<NFA> ThompsonConstruction::buildConcat(shared_ptr<ConcatNode> node) {
  auto leftNFA = build(node->left);
  auto rightNFA = build(node->right);

  // 将leftNFA的接受状态连接到rightNFA的起始状态
  leftNFA->accept->addEpsilonTransition(rightNFA->start);
  leftNFA->accept->isAccepting = false;

  return make_shared<NFA>(leftNFA->start, rightNFA->accept);
}

// 并的NFA：NFA1 | NFA2
shared_ptr<NFA> ThompsonConstruction::buildUnion(shared_ptr<UnionNode> node) {
  auto leftNFA = build(node->left);
  auto rightNFA = build(node->right);

  // 创建新的起始和接受状态
  auto newStart = make_shared<NFAState>(getNextStateId());
  auto newAccept = make_shared<NFAState>(getNextStateId());

  // 从新起始状态通过epsilon转换到两个NFA的起始状态
  newStart->addEpsilonTransition(leftNFA->start);
  newStart->addEpsilonTransition(rightNFA->start);

  // 从两个NFA的接受状态通过epsilon转换到新接受状态
  leftNFA->accept->addEpsilonTransition(newAccept);
  rightNFA->accept->addEpsilonTransition(newAccept);
  leftNFA->accept->isAccepting = false;
  rightNFA->accept->isAccepting = false;

  return make_shared<NFA>(newStart, newAccept);
}

// Kleene闭包的NFA：NFA*
shared_ptr<NFA> ThompsonConstruction::buildStar(shared_ptr<StarNode> node) {
  auto childNFA = build(node->child);

  // 创建新的起始和接受状态
  auto newStart = make_shared<NFAState>(getNextStateId());
  auto newAccept = make_shared<NFAState>(getNextStateId());

  // 从新起始状态通过epsilon转换到childNFA的起始状态和新接受状态（0次）
  newStart->addEpsilonTransition(childNFA->start);
  newStart->addEpsilonTransition(newAccept);

  // 从childNFA的接受状态通过epsilon转换到childNFA的起始状态（循环）和新接受状态
  childNFA->accept->addEpsilonTransition(childNFA->start);
  childNFA->accept->addEpsilonTransition(newAccept);
  childNFA->accept->isAccepting = false;

  return make_shared<NFA>(newStart, newAccept);
}

// 正闭包的NFA：NFA+（要求至少匹配一次）
shared_ptr<NFA> ThompsonConstruction::buildPlus(shared_ptr<PlusNode> node) {
  // 只构建一次childNFA
  auto childNFA = build(node->child);

  // 创建新的起始和接受状态
  auto newStart = make_shared<NFAState>(getNextStateId());
  auto newAccept = make_shared<NFAState>(getNextStateId());

  // 从新起始状态必须通过childNFA（至少一次）
  newStart->addEpsilonTransition(childNFA->start);

  // 从childNFA的接受状态通过epsilon转换到childNFA的起始状态（循环，0次或多次）
  // 和到新接受状态（结束）
  childNFA->accept->addEpsilonTransition(childNFA->start);
  childNFA->accept->addEpsilonTransition(newAccept);
  childNFA->accept->isAccepting = false;

  return make_shared<NFA>(newStart, newAccept);
}

// 任意字符的NFA：匹配除换行符外的所有字符
shared_ptr<NFA> ThompsonConstruction::buildAny(shared_ptr<AnyNode> node) {
  auto start = make_shared<NFAState>(getNextStateId());
  auto accept = make_shared<NFAState>(getNextStateId());

  // 为所有字符（0-255）添加转换，除了换行符 \n (10)
  for (int i = 0; i < 256; i++) {
    if (i != '\n') {
      start->addTransition(static_cast<char>(i), accept);
    }
  }

  return make_shared<NFA>(start, accept);
}

// Epsilon的NFA
shared_ptr<NFA>
ThompsonConstruction::buildEpsilon(shared_ptr<EpsilonNode> node) {
  auto start = make_shared<NFAState>(getNextStateId());
  auto accept = make_shared<NFAState>(getNextStateId());

  start->addEpsilonTransition(accept);

  return make_shared<NFA>(start, accept);
}
