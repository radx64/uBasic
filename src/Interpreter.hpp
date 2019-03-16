#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <list>
#include <string>
#include <ostream>

#include "Token.hpp"

class Expression;

class Interpreter
{
public:
    Interpreter(std::ostream& output_stream);
    void run(std::string program);

private:
    Token evaluate_tree(Expression* expression_tree);
    Token evaluate_math_operations(Expression* expression_tree, Type math_operator);
    Expression* parse_tree_;
    std::ostream& output_stream_;
};

#endif  // INTERPRETER_HPP_
