#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <list>
#include <string>
#include <iterator>

#include "Token.hpp"

class Lexer
{
public:
    Lexer() : currentToken_(Type::ENDOFFILE, std::string("")){}

    TokenList tokenize(std::string source)
    {
        source_ = source;
        position_ = source_.begin();
        do
        {
            currentToken_ = getNextToken();
            tokens_.push_back(currentToken_);
        }
        while (currentToken_.getType() != Type::ERROR && currentToken_.getType() != Type::ENDOFFILE);  
        return tokens_;
    }

private:
    Token getNextToken()
    {
        Token token(Type::ENDOFFILE, std::string(""));

        while(*position_ == ' ')
        {
            position_++;
        }

        if (isdigit(*position_))
        {
            std::string number("");
            number += *position_;
            while(isdigit(*(position_ + 1)))
            {
                number += *(position_ + 1);
                position_++;
            }
            token = Token(Type::NUMBER, std::string("") + number);

        }
        else if ((*position_) == '+')
        {
            token = Token(Type::PLUS);
        }
        else if ((*position_) == '-')
        {
            token = Token(Type::MINUS);
        }
        else if ((*position_) == '*')
        {
            token = Token(Type::MULTIPLY);
        }
        else if ((*position_) == '/')
        {
            token = Token(Type::DIVIDE);
        }

        else if ((*position_) == '\0')
        {
            position_++;
            return token;
   
        }
        else
        {
            token = Token(Type::ERROR, std::string("at position ") + std::to_string(std::distance(source_.begin(), position_)));
        }

        position_++;
        return token;
    }

    Token currentToken_;
    std::string source_;
    std::string::iterator position_;
    TokenList tokens_;  
};

#endif  // LEXER_HPP_