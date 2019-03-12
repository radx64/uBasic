#include "Parser.hpp"
#include <iostream>

#include "Expression.hpp"
#include "Token.hpp"

Expression* Parser::build(const std::list<Token>& tokens)
{
    Expression* current_node = new Expression;
    for (const auto& token : tokens)
    {
        std::clog << token.toString() << std::endl;

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
        else if (token.getType() == Type::PLUS || token.getType() == Type::MINUS)
        {
            Expression* new_node = new Expression;
            current_node->parent = new_node;
            Expression* old_node = current_node;
            current_node = new_node;
            current_node->value = token;
            current_node->left_child = old_node;
        }
        else if (token.getType() == Type::MULTIPLY || token.getType() == Type::DIVIDE)
        {
            auto current_node_type = current_node->value.getType();
            if (current_node_type == Type::PLUS || current_node_type == Type::MINUS) //lower prio operators
            {
                Expression* old_right_child = current_node->right_child;
                Expression* new_node = new Expression;
                new_node->parent = current_node;
                new_node->value = token;
                new_node->left_child = old_right_child;
                old_right_child->parent = new_node;
                current_node->right_child = new_node;
                current_node = new_node;
            }
            else
            {
                Expression* new_node = new Expression;
                current_node->parent = new_node;
                Expression* old_node = current_node;
                current_node = new_node;
                current_node->value = token;
                current_node->left_child = old_node;
            }
        }
        else if (token.getType() == Type::ENDOFFILE){}
        else
        {   
            std::clog << "ERROR while building parse tree! Unknown token type" << std::endl;
        }

    }

    Expression* top_node = current_node;

    while (top_node->parent != nullptr) top_node = top_node->parent;

    return top_node;
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