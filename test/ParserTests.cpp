#include <gtest/gtest.h>

#include "Parser.hpp"

#include "Expression.hpp"
#include "Token.hpp"

TEST(ParserShould, createCorrectTreeForPlusOperator)
{
    std::list<Token> input = 
    {
        Token{Type::NUMBER, "1"},
        Token{Type::PLUS},
        Token{Type::NUMBER, "2"}
    };
    Expression* expression = Parser::build(input);

    /* Expected parse tree 
         +          
        1 2
    */

    EXPECT_EQ(expression->value, Token(Type::PLUS));
    EXPECT_EQ(expression->parent, nullptr);

    EXPECT_EQ(expression->left_child->value, Token(Type::NUMBER, "1"));
    EXPECT_EQ(expression->left_child->parent->value, Token(Type::PLUS));

    EXPECT_EQ(expression->right_child->value, Token(Type::NUMBER, "2"));
    EXPECT_EQ(expression->right_child->parent->value, Token(Type::PLUS));
    Parser::destroy(expression);
}

TEST(ParserShould, createCorrectTreeForPlusOperatorWithMoreElements)
{
    std::list<Token> input = 
    {
        Token{Type::NUMBER, "1"},
        Token{Type::PLUS},
        Token{Type::NUMBER, "2"},
        Token{Type::PLUS},
        Token{Type::NUMBER, "3"}
    };
    Expression* expression = Parser::build(input);

    /* Expected parse tree 
         +          
        + 3
       1 2
    */

    EXPECT_EQ(expression->value, Token(Type::PLUS));
    EXPECT_EQ(expression->parent, nullptr);

    EXPECT_EQ(expression->left_child->value, Token(Type::PLUS));
    EXPECT_EQ(expression->left_child->parent->value, Token(Type::PLUS)); 

    EXPECT_EQ(expression->right_child->value, Token(Type::NUMBER, "3"));
    EXPECT_EQ(expression->right_child->parent->value, Token(Type::PLUS)); 

    Expression* left_branch = expression->left_child;

    EXPECT_EQ(left_branch->value, Token(Type::PLUS));
    EXPECT_EQ(left_branch->parent->value, Token(Type::PLUS));

    EXPECT_EQ(left_branch->left_child->value, Token(Type::NUMBER, "1"));
    EXPECT_EQ(left_branch->left_child->parent->value, Token(Type::PLUS)); 

    EXPECT_EQ(left_branch->right_child->value, Token(Type::NUMBER, "2"));
    EXPECT_EQ(left_branch->right_child->parent->value, Token(Type::PLUS)); 
    Parser::destroy(expression);
}

TEST(ParserShould, createCorrectTreeForPlusAndMultiplyOperators)
{
    std::list<Token> input = 
    {
        Token{Type::NUMBER, "1"},
        Token{Type::PLUS},
        Token{Type::NUMBER, "2"},
        Token{Type::MULTIPLY},
        Token{Type::NUMBER, "3"}
    };
    Expression* expression = Parser::build(input);

    /* Expected parse tree 
         +          
        1 *
         2 3
    */

    EXPECT_EQ(expression->value, Token(Type::PLUS));
    EXPECT_EQ(expression->parent, nullptr);

    EXPECT_EQ(expression->left_child->value, Token(Type::NUMBER, "1"));
    EXPECT_EQ(expression->left_child->parent->value, Token(Type::PLUS)); 
    EXPECT_EQ(expression->right_child->value, Token(Type::MULTIPLY));    
    EXPECT_EQ(expression->right_child->parent->value, Token(Type::PLUS)); 

     Expression* right_branch = expression->right_child;

    EXPECT_EQ(right_branch->value, Token(Type::MULTIPLY));
    EXPECT_EQ(right_branch->parent->value, Token(Type::PLUS));

    EXPECT_EQ(right_branch->left_child->value, Token(Type::NUMBER, "2"));
    EXPECT_EQ(right_branch->left_child->parent->value, Token(Type::MULTIPLY)); 

    EXPECT_EQ(right_branch->right_child->value, Token(Type::NUMBER, "3"));
    EXPECT_EQ(right_branch->right_child->parent->value, Token(Type::MULTIPLY)); 
    Parser::destroy(expression);
}