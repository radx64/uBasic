#include <Lexer.hpp>

const std::map<std::string, Type> stringToKeywordType = 
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

TokenList Lexer::tokenize(std::string source)
{
    Token currentToken{Type::ENDOFFILE, std::string("")};
    TokenList tokens; 

    source_ = source;
    position_ = source_.begin();
    do
    {
        currentToken = getNextToken();
        tokens.push_back(currentToken);
    }
    while (currentToken.getType() != Type::ERROR && currentToken.getType() != Type::ENDOFFILE);  
    return tokens;
}

std::string Lexer::getNextKeyword()
{
    for (auto keyword : stringToKeywordType)
    {
        if (std::equal(keyword.first.begin(), keyword.first.end(), position_))
        {
            position_ += keyword.first.size();
            return keyword.first;
        }
    }
    return std::string();
}

Token Lexer::makeKeywordToken(std::string keyword)
{
    auto result = stringToKeywordType.find(keyword);
    if (result != stringToKeywordType.end())
    {
        return Token{(*result).second};
    }
    else
    {
        return Token{Type::ERROR};
    }
}

std::string Lexer::getNextVariable()
{
    std::string variableName;

    while(*position_ != ' ' && *position_ != '\0')
    {
        variableName += *position_;
        position_++;
    }

    return variableName;
}

Token Lexer::makeVariableToken(std::string variableName)
{
    return Token{Type::VARIABLE, variableName};
}

Token Lexer::makeStringToken()
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
    return Token(Type::STRING, str);
}

Token Lexer::getNextToken()
{
    Token token{Type::ENDOFFILE};

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

    else if ((*position_) == '\0' || position_ == source_.end())
    {
        token = Token{Type::ENDOFFILE};
    }
    else if ((*position_) == '\"')
    {
        token = makeStringToken();
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