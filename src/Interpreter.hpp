#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include <list>
#include <string>

enum class Type
{
    ENDOFFILE,
    INTEGER,
    OPERATOR
};

std::string toString(const Type& type);

class Token
{
public:
    Token(Type type, std::string value): type_(type), value_(value) {}

    std::string toString(){ return std::string("{") + ::toString(type_) + ", " + value_ + "}";}
    Type getType(){return type_;}
    std::string getValue(){return value_;}

private:
    Type type_;
    std::string value_;
};


class Interpreter
{
public:
    Interpreter();
    void run(std::string program);

private:
    Token* getNextToken();
    void tokenize();
    void evaluate();
    Token* eat(Type t);
    Token* currentToken_;
    std::string::iterator position_;
    std::list<Token*> tokens_; 
};

#endif  // INTERPRETER_HPP_