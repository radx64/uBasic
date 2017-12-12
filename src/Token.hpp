#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <list>
#include <string>

enum class Type
{
    //Valued eLements
    ERROR,
    NUMBER,
    STRING,
    VARIABLE,
    //Non valued elements
    DIVIDE,
    ENDOFFILE,
    MINUS,
    MULTIPLY,
    PLUS,
    //Keywords
    END,
    FOR,
    GOTO,
    IF,
    INPUT,
    LET,
    LIST,
    NEXT,
    PRINT,
    RUN,
};

const std::string toString(const Type& type); // this will be removed

class Token
{
public:
    Token(Type type);
    Token(Type type, std::string value);

    const std::string toString() const;
    const Type& getType() const;
    const std::string& getValue() const;
    friend bool operator==(const Token lhs, const Token rhs);

private:
    Type type_;
    std::string value_;
};

bool operator==(const Token lhs, const Token rhs);

using TokenList = std::list<Token>;

#endif  // TOKEN_HPP_
