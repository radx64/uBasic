#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <list>

class Expression;
class Token;

class Parser
{
public:
    //this can be a static method right now, so I don't even need this whole class thing
    static Expression* build(const std::list<Token>& tokens);
    static void destroy(Expression* expression);
    static void debug_traverse_tree(Expression* start, int depth);
};

#endif  // PARSER_HPP_