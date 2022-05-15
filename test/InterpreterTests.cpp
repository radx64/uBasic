#include <algorithm>
#include <sstream>

#include <gtest/gtest.h>

#include "Interpreter.hpp"

class InterpreterShould : public ::testing::Test
{
public:
InterpreterShould() : interpreter_(output_)
{}

    Interpreter interpreter_;
    std::stringstream output_;
};

std::string sanitize(std::string str)
{
    std::string output = str;
    output.erase(std::remove_if(output.begin(), output.end(), 
        []( char const& c ) { return !std::isalnum(c); } ), output.end());
    return output;
}

TEST_F(InterpreterShould, addTwoNumbers)
{
    interpreter_.run("2+2");
    EXPECT_EQ(sanitize(output_.str()), "4");
}

TEST_F(InterpreterShould, addTwoNumbersWithSpaces)
{
    interpreter_.run("1 + 7");
    EXPECT_EQ(sanitize(output_.str()), "8");
}

TEST_F(InterpreterShould, addThreeNumbers)
{
    interpreter_.run("1 + 2 + 3");
    EXPECT_EQ(sanitize(output_.str()), "6");
}

TEST_F(InterpreterShould, multiplyAndAddInCorrectOrder)
{
    interpreter_.run("1 + 2 * 3");
    EXPECT_EQ(sanitize(output_.str()), "7");
}

TEST_F(InterpreterShould, multiplyAndAddInCorrectOrderWhenMultiplicationFirst)
{
    interpreter_.run("1 * 2 + 3");
    EXPECT_EQ(sanitize(output_.str()), "5");
}