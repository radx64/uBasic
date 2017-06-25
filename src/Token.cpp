#include "Token.hpp"

#include <iostream>

std::string toString(const Type& type)
{
    switch (type)
    {
        case Type::ENDOFFILE  : return "ENDOFFILE";
        case Type::ERROR      : return "ERROR";
        case Type::NUMBER     : return "NUMBER";
        case Type::PLUS       : return "PLUS";
        case Type::MINUS      : return "MINUS";
        case Type::MULTIPLY   : return "MULTIPLY";
        case Type::DIVIDE     : return "DIVIDE";
        case Type::STRING     : return "STRING";
        default               : return "UNKNOWN";
    }
}

Token::Token(Type type, std::string value): type_(type), value_(value)
{

}
Token::Token(Type type): type_(type), value_("")
{

}

std::string Token::toString() const
{
    return std::string("{") + ::toString(type_) + ", " + value_ + "}";
}

Type Token::getType() const
{
    return type_;
}

std::string Token::getValue() const
{
    return value_;
}

bool operator==(const Token lhs, const Token rhs)
{
    return ((lhs.type_ == rhs.type_) && (lhs.value_ == rhs.value_));
}

std::ostream& operator<<(std::ostream& stream, const Token t)
{
    stream << t.toString();
    return stream;
}

