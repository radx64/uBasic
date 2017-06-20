#include "Token.hpp"

std::string toString(const Type& type)
{
    switch (type)
    {
        case Type::ENDOFFILE  : return "ENDOFFILE";
        case Type::ERROR      : return "ERROR";
        case Type::INTEGER    : return "INTEGER";
        case Type::OPERATOR   : return "OPERATOR";
        default               : return "UNKNOWN";
    }
}

Token::Token(Type type, std::string value): type_(type), value_(value)
{

}

std::string Token::toString()
{
    return std::string("{") + ::toString(type_) + ", " + value_ + "}";
}

Type Token::getType()
{
    return type_;
}

std::string Token::getValue()
{
    return value_;
}


