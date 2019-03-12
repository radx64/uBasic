#include "Interpreter.hpp"

#include <cctype>
#include <iostream>

#include "Expression.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

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
    parse_tree_ = Parser::build(tokens_);
    std::clog << "Some debug parse tree below"<< std::endl;
    Parser::debug_traverse_tree(parse_tree_, 0);
    evaluate();
    Parser::destroy(parse_tree_);
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
}
