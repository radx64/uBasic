#include <Token.hpp>

struct Expression
{
    Expression* parent = nullptr;
    Expression* left_child = nullptr;
    Expression* right_child = nullptr;
    Token value {Type::ENDOFFILE};
};