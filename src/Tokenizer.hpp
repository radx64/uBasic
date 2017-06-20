#ifndef TOKENIZER_HPP_
#define TOKENIZER_HPP_

#include <list>
#include <string>

#include "Token.hpp"

class Tokenizer
{
public:
    Tokenizer() : currentToken_(Type::ENDOFFILE, std::string("")){}

    TokenList tokenize(std::string source)
    {
        position_ = source.begin();
        do
        {
            currentToken_ = getNextToken();
            std::cout << currentToken_.toString() << std::endl;
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
            std::string integer("");
            integer += *position_;
            while(isdigit(*(position_ + 1)))
            {
                integer += *(position_ + 1);
                position_++;
            }
            token = Token(Type::INTEGER, std::string("") + integer);

        }
        else if ((*position_) == '+' || (*position_) == '-' || (*position_) == '*' || (*position_) == '/' )
        {
            token = Token(Type::OPERATOR, std::string("") + (*position_));
        }

        position_++;
        return token;
    }

    Token currentToken_;
    std::string::iterator position_;
    TokenList tokens_;  
};

#endif  // TOKENIZER_HPP_