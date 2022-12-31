#include <string>
#include <iostream>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ActionParams.hpp"
#include "CLILoader.hpp"

using namespace std::string_literals;

class CLILoaderTest: public ::testing::Test
{
public:
    CLILoader cLILoader{};
};

TEST_F(CLILoaderTest, GivenEmptyStringToParseWhenParseMethodIsCalledExpectReturningEmptyActionParams)
{
    auto emptyString = ""s;
    
    auto results = cLILoader.parse(emptyString);
    
    auto expectedOutput = ActionParams{};
    EXPECT_EQ(results, expectedOutput);
}

TEST_F(CLILoaderTest, GivenOneWordStringToParseWhenParseMethodIsCalledExpectCLILoaderParseString)
{
    auto oneWordString = "MakeDinner"s;
    
    auto results = cLILoader.parse(oneWordString);

    auto expectedOutput = ActionParams{"MakeDinner", {}};
    EXPECT_EQ(results, expectedOutput);
}

TEST_F(CLILoaderTest, GivenTwoWordStringToParseWhenParseMethodIsCalledExpectCLILoaderParseString)
{
    auto twoWordString = "MakeDinner 2"s;

    auto results = cLILoader.parse(twoWordString);

    auto expectedOutput = ActionParams{"MakeDinner", "2"};
    EXPECT_EQ(results, expectedOutput);
}

TEST_F(CLILoaderTest, GivenSixWordStringToParseWhenParseMethodIsCalledExpectCLILoaderParseString)
{
    auto sixWordString = "MakeDinner 2 cola pancake table spoil"s;
    
    auto results = cLILoader.parse(sixWordString);
    
    auto expectedOutput = ActionParams{"MakeDinner", "2 cola pancake table spoil"};
    EXPECT_EQ(results, expectedOutput);
}
