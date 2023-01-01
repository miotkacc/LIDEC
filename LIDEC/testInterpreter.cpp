#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Interpreter.hpp"


TEST(Interpreter, GivenConfigStringXMLExtractDict)
{

}

TEST(Interpreter, GivenStringWhenstringToVectorMethodIsCalledWithStringSeparatedWithSpacesExpectVectorOfString)
{
    std::vector<std::string> expectedVectorOfStrings{"1", "2", "potatoes"};
    Interpreter interpreter;
    auto returnedVectorOfStrings = interpreter.stringToVector("1 2 potatoes");
    EXPECT_EQ(expectedVectorOfStrings, returnedVectorOfStrings);
}