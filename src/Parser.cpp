#include "Parser.hpp"
#include <iostream>

#include "Expression.hpp"
#include "Token.hpp"


/*
    TODO: Token replace methods need to be tested in UT. As there are much parent child operations that I can forget.
*/

/*
    push_node_to_left_with_token moves given node down and create one from token
    [1]  -> Token(+) ->  [+]
                        1
    Pointer passed to function will be modified (so *& is necessary)
*/

void push_node_to_left_with_token(Expression*& node, const Token& token)
{
    Expression* new_node = new Expression;
    new_node->parent = node->parent;
    node->parent = new_node;
    Expression* old_node = node;
    node = new_node;
    node->value = token;
    node->left_child = old_node;
    if(node->parent)
    {
        if (node->parent->left_child == old_node) node->parent->left_child = node;
        if (node->parent->right_child == old_node) node->parent->right_child = node;
    }
}

/*
    push_right_node_deeper_and_replace_with moves right child of given node down and create one from token
    [+]  -> Token(*) ->    +
    1 1                  1 [*]
                          1
    Pointer passed to function will be modified (so *& is necessary)

    [TODO]: With proper usage of push_node_to_left_with_token same behaviour can be achieved, 
    so I need to think about using it.Also i need better way to keep track of current node, 
    at least to be deterministic.
*/

void push_right_node_deeper_and_replace_with(Expression*& node, const Token& token)
{
    Expression* old_right_child = node->right_child;
    Expression* new_node = new Expression;
    new_node->parent = node;
    new_node->value = token;
    new_node->left_child = old_right_child;
    old_right_child->parent = new_node;
    node->right_child = new_node;
    node = new_node;    
}

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
        else if (token.getType() == Type::PLUS || token.getType() == Type::MINUS)
        {
            push_node_to_left_with_token(current_node, token);
        }
        else if (token.getType() == Type::MULTIPLY || token.getType() == Type::DIVIDE)
        {
            auto current_node_type = current_node->value.getType();
            if (current_node_type == Type::PLUS || current_node_type == Type::MINUS) //lower prio operators
            {
                push_right_node_deeper_and_replace_with(current_node, token);
            }
            else
            {
                push_node_to_left_with_token(current_node, token);
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
    if (start->right_child != nullptr) debug_traverse_tree(start->right_child, depth + 1);
    
    for (int i=0; i < depth; ++i) std::clog << "   "; 
    std::clog << start->value.toString() << std::endl;
    
    if (start->left_child != nullptr) debug_traverse_tree(start->left_child, depth + 1);
}