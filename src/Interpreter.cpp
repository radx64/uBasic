#include "Interpreter.hpp"

#include <cctype>
#include <iostream>

std::string toString(const Type& type)
{
    switch (type)
    {
        case Type::ENDOFFILE : return "ENDOFFILE";
        case Type::INTEGER : return "INTEGER";
        case Type::OPERATOR : return "OPERATOR";
        default : return "UNKNOWN";
    }
}

Interpreter::Interpreter(){}

void Interpreter::run(std::string program)
{
    std::cout << "Parsing:" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << program << std::endl;
    std::cout << "----------------------" << std::endl;

    position_ = program.begin();

    for(auto t : tokens_)
    {
        if (t) delete t;
    }

    tokens_.clear();

    tokenize();
    evaluate();
}

Token* Interpreter::getNextToken()
{
    Token* token = nullptr;

    while(*position_ == ' ')
    {
        position_++;
    }

    if (isdigit(*position_))
    {
        std::string integer("");
        integer += *position_;
        while(isdigit(*(position_ + 1)))
        {
            integer += *(position_ + 1);
            position_++;
        }
        token = new Token(Type::INTEGER, std::string("") + integer);

    }
    else if ((*position_) == '+' || (*position_) == '-' || (*position_) == '*' || (*position_) == '/' )
    {
        token = new Token(Type::OPERATOR, std::string("") + (*position_));
    }

    position_++;

    if (!token) return new Token(Type::ENDOFFILE, std::string(""));
    else return token;
}

void Interpreter::tokenize()
{
    do
    {
        currentToken_ = getNextToken();

        if (currentToken_ != nullptr)
        {
            std::cout << currentToken_->toString() << std::endl;
            tokens_.push_back(currentToken_);
        }
    }
    while (currentToken_ != nullptr && currentToken_->getType() != Type::ENDOFFILE);   
}

Token* Interpreter::eat(Type t)
{
    if (tokens_.empty()) return nullptr;

    Token* token = tokens_.front();
    if (token->getType() == t)  
    {
        tokens_.pop_front();
        return token;
    }
    else
    {
       std::cout << "Error! Wrong argument type" << std::endl; 
       std::cout << "Expected: " << ::toString(t) << " has: " << toString(token->getType()) << std::endl; 
       return nullptr;
    }
}

void Interpreter::evaluate()
{
    int arg1 = std::stoi(eat(Type::INTEGER)->getValue());
    std::string oper = eat(Type::OPERATOR)->getValue();
    int arg2 = std::stoi(eat(Type::INTEGER)->getValue());

    switch (oper[0])
    {
        case '+' : std::cout << arg1 + arg2 << std::endl; break;
        case '-' : std::cout << arg1 - arg2 << std::endl; break;
        case '*' : std::cout << arg1 * arg2 << std::endl; break;
        case '/' : std::cout << arg1 / arg2 << std::endl; break;
        default : std::cout << "Unknown operand" << std::endl; break;
    }
}