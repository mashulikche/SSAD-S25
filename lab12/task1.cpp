#include <iostream>
#include <memory>

using namespace std;

class Expression;

using ExpressionPtr = shared_ptr<Expression>;

class Expression {
public:
    virtual ~Expression() = default;
    virtual double evaluate() const = 0;
};

class NumberExpression : public Expression {
    double value;
public:
    explicit NumberExpression(double val) : value(val) {}
    double evaluate() const override { return value; }
};

class AddExpression : public Expression {
    ExpressionPtr left;
    ExpressionPtr right;
public:
    AddExpression(ExpressionPtr l, ExpressionPtr r) : left(l), right(r) {}
    double evaluate() const override {
        return left->evaluate() + right->evaluate();
    }
};

class SubtractExpression : public Expression {
    ExpressionPtr left;
    ExpressionPtr right;
public:
    SubtractExpression(ExpressionPtr l, ExpressionPtr r) : left(l), right(r) {}
    double evaluate() const override {
        return left->evaluate() - right->evaluate();
    }
};

class MultiplyExpression : public Expression {
    ExpressionPtr left;
    ExpressionPtr right;
public:
    MultiplyExpression(ExpressionPtr l, ExpressionPtr r) : left(l), right(r) {}
    double evaluate() const override {
        return left->evaluate() * right->evaluate();
    }
};

ExpressionPtr number(double value) {
    return make_shared<NumberExpression>(value);
}

ExpressionPtr add(ExpressionPtr left, ExpressionPtr right) {
    return make_shared<AddExpression>(left, right);
}

ExpressionPtr subtract(ExpressionPtr left, ExpressionPtr right) {
    return make_shared<SubtractExpression>(left, right);
}

ExpressionPtr multiply(ExpressionPtr left, ExpressionPtr right) {
    return make_shared<MultiplyExpression>(left, right);
}

int main() {
    ExpressionPtr expr = multiply(
            add(number(13), number(39)),
            subtract(number(56), number(4))
    );

    cout << "(13 + 39) * (56 - 4) = "<< expr->evaluate() << endl;
    
    ExpressionPtr complexExpr = subtract(
            multiply(
                    number(2),
                    add(number(16), number(14))
            ),
            number(8)
    );

    cout << "\n 2 * (16 + 14) - 8 = " << complexExpr->evaluate() << endl;

    return 0;
}