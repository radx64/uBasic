#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include "Token.hpp"

const std::map<std::string, Type> stringToTypeMapping = 
{
    {"END",   Type::END},
    {"FOR",   Type::FOR},
    {"GOTO",  Type::GOTO},
    {"IF",    Type::IF},
    {"INPUT", Type::INPUT},
    {"LET",   Type::LET},
    {"LIST",  Type::LIST},
    {"NEXT",  Type::NEXT},
    {"PRINT", Type::PRINT},
    {"RUN",   Type::RUN},    
};

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
    std::string getNextKeyword()
    {
        for (auto keyword : stringToTypeMapping)
        {
            if (std::equal(keyword.first.begin(), keyword.first.end(), position_))
            {
                position_ += keyword.first.size();
                return keyword.first;
            }
        }
        return "";
    }

    Token makeKeywordToken(std::string keyword)
    {
        auto result = stringToTypeMapping.find(keyword);
        if (result != stringToTypeMapping.end())
        {
            return Token{(*result).second};
        }
        else
        {
            return Token{Type::ERROR};
        }
    }

    std::string getNextVariable()
    {
        std::string variableName;

        while(*position_ != ' ' && *position_ != '\0')
        {
            variableName += *position_;
            position_++;
        }

        return variableName;
    }

    Token makeVariableToken(std::string variableName)
    {
        return Token{Type::VARIABLE, variableName};
    }

    Token getNextToken()
    {
        Token token(Type::ENDOFFILE);

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
            token = Token(Type::NUMBER, number);
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
        else if ((*position_) == '\"')
        {
            auto beginQuoteIndex = std::distance(source_.begin(), position_);
            std::string str("");
            position_++;
            while( (*position_) != '\"')
            {
                if (*(position_) == '\0')
                {
                    return Token{Type::ERROR, std::string("missing \" at end of a string starting at ") + std::to_string(beginQuoteIndex)};
                }
                str += *position_;
                position_++;
            }
            token = Token(Type::STRING, str);
        }
        else
        {
            std::string keyword = getNextKeyword();
            if (keyword.size() > 0)
            {
                return makeKeywordToken(keyword);
            }

            std::string variable = getNextVariable();
            if (variable.size() > 0)
            {
                return makeVariableToken(variable);
            }

            return Token{Type::ERROR, std::string("at position ") + std::to_string(std::distance(source_.begin(), position_))};
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