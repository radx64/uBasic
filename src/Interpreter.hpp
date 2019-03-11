#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <list>
#include <string>
#include <ostream>
#include "Token.hpp"

// TODO:
// need to introduce some AST
// expr   : term ((PLUS | MINUS) term)*
// term   : factor ((MUL | DIV) factor)*
// factor : INTEGER | LPAREN expr RPAREN

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
    std::ostream& output_stream_;
};

#endif  // INTERPRETER_HPP_
