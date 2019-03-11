#include "Interpreter.hpp"

#include <cctype>
#include <iostream>

#include "Lexer.hpp"

Interpreter::Interpreter(std::ostream& output_stream) : output_stream_(output_stream)
{}

void Interpreter::run(std::string program)
{
    std::clog << "Parsing:\n";
    std::clog << "----------------------\n";
    std::clog << program << "\n";
    std::clog << "----------------------" << std::endl;

    tokens_.clear();

    Lexer lex;

    tokens_ = lex.tokenize(program);
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

Type Interpreter::getNextTokenType()
{
    return tokens_.front().getType();
}

void Interpreter::evaluate()
{
    for (const auto& token : tokens_)
    {
        std::clog << toString(token.getType()) << std::endl;
    }

    auto firstTokenType = getNextTokenType();

    switch(firstTokenType)
    {
        case Type::NUMBER : break;
        default: break;
    }

    int arg1 = std::stoi(eat(Type::NUMBER).getValue());
    eat(Type::PLUS);
    int arg2 = std::stoi(eat(Type::NUMBER).getValue());

    output_stream_ << arg1 + arg2 << std::endl;
}
