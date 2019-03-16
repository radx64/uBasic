#include "Interpreter.hpp"

#include <cctype>
#include <iostream>
#include <string>

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
    Lexer lex;
    TokenList tokens = lex.tokenize(program);
    parse_tree_ = Parser::build(tokens);
    Token result = evaluate_tree(parse_tree_);
    output_stream_ << result.getValue();
    std::clog << "Output:" << result.getValue() << std::endl;
    // std::clog << "Some debug parse tree below"<< std::endl;
    // Parser::debug_traverse_tree(parse_tree_, 0);
    Parser::destroy(parse_tree_);
}


Token Interpreter::evaluate_math_operations(Expression* expression_tree, Type math_operator)
{
    Token left_operand = evaluate_tree(expression_tree->left_child);
    Token right_operand = evaluate_tree(expression_tree->right_child);

    if (left_operand.getType() != Type::NUMBER) return Token(Type::ERROR);
    if (right_operand.getType() != Type::NUMBER) return Token(Type::ERROR);

    uint32_t left_operand_value = std::stoi(left_operand.getValue());
    uint32_t right_operand_value = std::stoi(right_operand.getValue());
    switch (math_operator)
    {
        case Type::PLUS : return Token(Type::NUMBER, std::to_string(left_operand_value + right_operand_value));   
        case Type::MINUS : return Token(Type::NUMBER, std::to_string(left_operand_value - right_operand_value));  
        case Type::MULTIPLY : return Token(Type::NUMBER, std::to_string(left_operand_value * right_operand_value));  
        case Type::DIVIDE : return Token(Type::NUMBER, std::to_string(left_operand_value / right_operand_value)); 
        default : return Token(Type::ERROR);    
    }
}

bool is_math_operator(const Type& operator_type)
{
    return operator_type == Type::PLUS || 
    operator_type == Type::MINUS || 
    operator_type == Type::MULTIPLY || 
    operator_type == Type::DIVIDE;
}

Token Interpreter::evaluate_tree(Expression* expression_tree)
{
    if(is_math_operator(expression_tree->value.getType()))
    {
        return evaluate_math_operations(expression_tree, expression_tree->value.getType());
    }

    if (expression_tree->value.getType() == Type::NUMBER) return expression_tree->value;

    if (expression_tree->left_child) evaluate_tree(expression_tree->left_child);
    if (expression_tree->right_child) evaluate_tree(expression_tree->right_child);


    return Token(Type::ERROR);
}
