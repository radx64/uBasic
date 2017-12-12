#include "Token.hpp"

#include <iostream>

const std::string toString(const Type& type)
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
        case Type::END        : return "END";
        case Type::FOR        : return "FOR";
        case Type::GOTO       : return "GOTO";
        case Type::IF         : return "IF";
        case Type::INPUT      : return "INPUT";
        case Type::LET        : return "LET";
        case Type::LIST       : return "LIST";
        case Type::NEXT       : return "NEXT";
        case Type::PRINT      : return "PRINT";
        case Type::RUN        : return "RUN";
        case Type::VARIABLE   : return "VARIABLE";        
        default               : return "UNKNOWN";
    }
}

Token::Token(Type type, std::string value): type_(type), value_(value)
{

}
Token::Token(Type type): type_(type), value_("")
{

}

const std::string Token::toString() const
{
    return std::string("{") + ::toString(type_) + ", " + value_ + "}";
}

const Type& Token::getType() const
{
    return type_;
}

const std::string& Token::getValue() const
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

