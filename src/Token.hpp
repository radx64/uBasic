#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <list>
#include <string>

enum class Type
{
    ENDOFFILE,
    ERROR,
    INTEGER,
    OPERATOR
};

std::string toString(const Type& type);

class Token
{
public:
    Token(Type type, std::string value);

    std::string toString();
    Type getType();
    std::string getValue();

private:
    Type type_;
    std::string value_;
};

using TokenList = std::list<Token>;

#endif  // TOKEN_HPP_
