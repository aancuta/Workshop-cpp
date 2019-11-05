#ifndef _EXPRESSION_FACTORY_H_
#define _EXPRESSION_FACTORY_H_

#include "Assignment.hpp"
#include "Block.hpp"
#include "ConditionalExpression.hpp"
#include "Expression.hpp"
#include "BinaryExpression.hpp"
#include "Identifier.hpp"
#include "PrintExpression.hpp"
#include "SymbolMap.hpp"
#include "UnaryExpression.hpp"

class ExpressionFactory {
public:
    std::unique_ptr<Undefined> makeUndefined();
    std::unique_ptr<Number> makeNumber(std::string&& text);
    std::unique_ptr<UnaryExpression> makeUnary(std::unique_ptr<Expression>&& expr, UnaryExpression::OP_TYPE opType);
    std::unique_ptr<BinaryExpression> makeBinary(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right, BinaryExpression::OP_TYPE opType);
    std::unique_ptr<Identifier> makeIdentifier(std::string&& text);
    std::unique_ptr<Assignment> makeAssignment(std::unique_ptr<Identifier>&& left, std::unique_ptr<Expression>&& right);
    std::unique_ptr<Block> makeBlock();
    std::unique_ptr<PrintExpression> makePrint(std::unique_ptr<Expression>&& expr);
    std::unique_ptr<ConditionalExpression> makeConditional(std::unique_ptr<Expression>&& condition, std::unique_ptr<Expression>&& thenExpr, std::unique_ptr<Expression>&& elseExpr);

private:
    SymbolMap _symbolMap;
};

#endif
