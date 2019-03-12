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
    Type getNextTokenType();

private:
    void evaluate();
    Token eat(Type t);
    TokenList tokens_;
    Expression* parse_tree_;
    std::ostream& output_stream_;
};

#endif  // INTERPRETER_HPP_
