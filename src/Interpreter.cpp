#include "Interpreter.hpp"

#include <cctype>
#include <iostream>

#include "Tokenizer.hpp"

Interpreter::Interpreter()
{

}

void Interpreter::run(std::string program)
{
    std::cout << "Parsing:" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << program << std::endl;
    std::cout << "----------------------" << std::endl;

    tokens_.clear();

    Tokenizer t;

    tokens_ = t.tokenize(program);
    evaluate();
}

Token Interpreter::eat(Type t)
{
    if (tokens_.empty()) return Token(Type::ENDOFFILE, std::string(""));

    Token& token = tokens_.front();
    if (token.getType() == t)  
    {
        tokens_.pop_front();
        return token;
    }
    else
    {
       std::cout << "Error! Wrong argument type" << std::endl; 
       std::cout << "Expected: " << ::toString(t) << " has: " << toString(token.getType()) << std::endl; 
       return Token(Type::ERROR, std::string(""));
    }
}

void Interpreter::evaluate()
{
    int arg1 = std::stoi(eat(Type::INTEGER).getValue());
    std::string oper = eat(Type::OPERATOR).getValue();
    int arg2 = std::stoi(eat(Type::INTEGER).getValue());

    switch (oper[0])
    {
        case '+' : std::cout << arg1 + arg2 << std::endl; break;
        case '-' : std::cout << arg1 - arg2 << std::endl; break;
        case '*' : std::cout << arg1 * arg2 << std::endl; break;
        case '/' : std::cout << arg1 / arg2 << std::endl; break;
        default : std::cout << "Unknown operand" << std::endl; break;
    }
}