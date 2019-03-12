#include "Parser.hpp"
#include <iostream>

#include "Expression.hpp"
#include "Token.hpp"

Expression* Parser::build(const std::list<Token>& tokens)
{
    Expression* current_node = new Expression;

    for (const auto& token : tokens)
    {
        if (token.getType() == Type::NUMBER)
        {
            if (current_node->left_child != nullptr)
            {
                Expression* new_node = new Expression;
                new_node->value = token;
                new_node->parent = current_node;
                current_node->right_child = new_node;
            }
            else
            {
                current_node->value = token;
            }
        }

        if (token.getType() == Type::PLUS)
        {
            Expression* new_node = new Expression;
            current_node->parent = new_node;
            Expression* old_node = current_node;
            current_node = new_node;
            current_node->value = token;
            current_node->left_child = old_node;
        }
    }
    return current_node;
}

void Parser::destroy(Expression* expression)
{
    if (expression->left_child != nullptr) Parser::destroy(expression->left_child);
    if (expression->right_child != nullptr) Parser::destroy(expression->right_child);
    if (expression->left_child == nullptr && expression->right_child == nullptr) delete expression;    
}

void Parser::debug_traverse_tree(Expression* start, int depth)
{
    if (start->left_child != nullptr) debug_traverse_tree(start->left_child, depth + 1);
    {
        for (int i=0; i < depth; ++i) std::clog << "   "; 
        std::clog << start->value.toString() << std::endl;
    }
    if (start->right_child != nullptr) debug_traverse_tree(start->right_child, depth + 1);
}