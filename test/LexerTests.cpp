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

TEST_F(LexerShould, detectEOFonEmptySource)
{
    auto tokens = lexer_.tokenize("");
    auto expected = TokenList{
        {Type::ENDOFFILE, ""}
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

TEST_F(LexerShould, detectEndToken)
{
    auto tokens = lexer_.tokenize("END");
    auto expected = TokenList{
        {Type::END},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectForToken)
{
    auto tokens = lexer_.tokenize("FOR");
    auto expected = TokenList{
        {Type::FOR},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectGotoToken)
{
    auto tokens = lexer_.tokenize("GOTO");
    auto expected = TokenList{
        {Type::GOTO},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectIfToken)
{
    auto tokens = lexer_.tokenize("IF");
    auto expected = TokenList{
        {Type::IF},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectInputToken)
{
    auto tokens = lexer_.tokenize("INPUT");
    auto expected = TokenList{
        {Type::INPUT},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectLetToken)
{
    auto tokens = lexer_.tokenize("LET");
    auto expected = TokenList{
        {Type::LET},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectListToken)
{
    auto tokens = lexer_.tokenize("LIST");
    auto expected = TokenList{
        {Type::LIST},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectNextToken)
{
    auto tokens = lexer_.tokenize("NEXT");
    auto expected = TokenList{
        {Type::NEXT},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectPrintToken)
{
    auto tokens = lexer_.tokenize("PRINT");
    auto expected = TokenList{
        {Type::PRINT},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectRunToken)
{
    auto tokens = lexer_.tokenize("RUN");
    auto expected = TokenList{
        {Type::RUN},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectVariable)
{
    auto tokens = lexer_.tokenize("ThatsNiceVariableName");
    auto expected = TokenList{
        {Type::VARIABLE, "ThatsNiceVariableName"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectLetWithVariable)
{
    auto tokens = lexer_.tokenize("LET X");
    auto expected = TokenList{
        {Type::LET},
        {Type::VARIABLE, "X"},
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}

TEST_F(LexerShould, detectVariableAfterFewTokens)
{
    auto tokens = lexer_.tokenize("10 20 30 Garbage");
    auto expected = TokenList{
        {Type::NUMBER, "10"},
        {Type::NUMBER, "20"},
        {Type::NUMBER, "30"},
        {Type::VARIABLE, "Garbage"},        
        {Type::ENDOFFILE, ""}
    };
    EXPECT_EQ(expected, tokens);
}