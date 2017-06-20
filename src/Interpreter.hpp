#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <list>
#include <string>

#include "Token.hpp"

class Interpreter
{
public:
    Interpreter();
    void run(std::string program);

private:
    void evaluate();
    Token eat(Type t);
    TokenList tokens_; 
};

#endif  // INTERPRETER_HPP_