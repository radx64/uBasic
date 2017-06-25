#include <gtest/gtest.h>

#include "Lexer.hpp"
#include "Token.hpp"

void PrintTo(const Token& t, std::ostream* os)
{
    *os << "\n" << t.toString();
}
void PrintTo(const TokenList& tl, std::ostream* os)
{
    for (auto t : tl)
    {
        *os << t.toString() << std::endl;
    }
}

class LexerShould : public ::testing::Test
{
protected:
    Lexer lexer_;

};

TEST_F(LexerShould, detectEOFonEmprySource)
{
    auto tokens = lexer_.tokenize("");
    auto expected = TokenList{
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectErrorOnGarbageSource)
{
    auto tokens = lexer_.tokenize("NotSoValidSource");
    auto expected = TokenList{
        {Type::ERROR, "at position 0"}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectSingleCharacterNumber)
{
    auto tokens = lexer_.tokenize("1");
    auto expected = TokenList{
        {Type::NUMBER, "1"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectMultipleCharacterNumber)
{
    auto tokens = lexer_.tokenize("1234");
    auto expected = TokenList{
        {Type::NUMBER, "1234"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectErrorAfterFewValidTokens)
{
    auto tokens = lexer_.tokenize("10 20 30 Garbage");
    auto expected = TokenList{
        {Type::NUMBER, "10"},
        {Type::NUMBER, "20"},
        {Type::NUMBER, "30"},
        {Type::ERROR, "at position 9"}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectPlusOperator)
{
    auto tokens = lexer_.tokenize("1+2");
    auto expected = TokenList{
        {Type::NUMBER, "1"},
        {Type::PLUS},
        {Type::NUMBER, "2"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectMinusOperator)
{
    auto tokens = lexer_.tokenize("1-2");
    auto expected = TokenList{
        {Type::NUMBER, "1"},
        {Type::MINUS},
        {Type::NUMBER, "2"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectMulitplyOperator)
{
    auto tokens = lexer_.tokenize("1*2");
    auto expected = TokenList{
        {Type::NUMBER, "1"},
        {Type::MULTIPLY},
        {Type::NUMBER, "2"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}
TEST_F(LexerShould, detectDivideOperator)
{
    auto tokens = lexer_.tokenize("1/2");
    auto expected = TokenList{
        {Type::NUMBER, "1"},
        {Type::DIVIDE},
        {Type::NUMBER, "2"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectSingleCharacterString)
{
    auto tokens = lexer_.tokenize("\"R\"");
    auto expected = TokenList{
        {Type::STRING, "R"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectMultiCharacterString)
{
    auto tokens = lexer_.tokenize("\"Radek was here\"");
    auto expected = TokenList{
        {Type::STRING, "Radek was here"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectErrorWithStringWhenMissingClosingQuote)
{
    auto tokens = lexer_.tokenize("\"Radek was here");
    auto expected = TokenList{
        {Type::ERROR, "missing \" at end of a string starting at 0"},
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectErrorWithStringWhenMissingClosingQuoteInMoreComplexSentence)
{
    auto tokens = lexer_.tokenize("10+20*30 \"Radek was here");
    auto expected = TokenList{
        {Type::NUMBER, "10"},
        {Type::PLUS},
        {Type::NUMBER, "20"},
        {Type::MULTIPLY},
        {Type::NUMBER, "30"},      
        {Type::ERROR, "missing \" at end of a string starting at 9"},
    };
    EXPECT_EQ(expected, tokens);
}