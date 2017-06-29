#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>

#include "Token.hpp"

class Lexer
{
public:
    Lexer() = default;
    TokenList tokenize(std::string source);

private:
    std::string getNextKeyword();
    Token makeKeywordToken(std::string keyword);
    std::string getNextVariable();
    Token makeVariableToken(std::string variableName);
    Token getNextToken();
    Token makeStringToken();

    std::string source_;
    std::string::iterator position_;
};

#endif  // LEXER_HPP_