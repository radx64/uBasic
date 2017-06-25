#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <list>
#include <string>

enum class Type
{
    ENDOFFILE,
    ERROR,
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};

std::string toString(const Type& type);

class Token
{
public:
    Token(Type type);
    Token(Type type, std::string value);

    std::string toString() const; 
    Type getType() const;
    std::string getValue() const;
    friend bool operator==(const Token lhs, const Token rhs);

private:
    Type type_;
    std::string value_;
};

bool operator==(const Token lhs, const Token rhs);

using TokenList = std::list<Token>;

#endif  // TOKEN_HPP_
