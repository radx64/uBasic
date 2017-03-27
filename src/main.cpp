#include <iostream>

#include "Interpreter.hpp"

int main()
{
    Interpreter interpreter;
    interpreter.run("21 + 39");
    interpreter.run("1 - 39");
    interpreter.run("6541 + 39");
    interpreter.run("14564 - 54339");
    return 0;
}