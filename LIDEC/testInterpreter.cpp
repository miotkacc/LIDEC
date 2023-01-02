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

TEST(Interpreter, GivenActionParamsAndFileContentWhenvalidateActionParamsAgainstConfigXMLMethodIsCalledThenExpectTrue){
    Interpreter interpreter;
    std::string fileContent = R"(<LIDEC><function name="MakePizza" paramsTypes="int"></function></LIDEC>)";
    auto returnedValue = interpreter.validateActionParamsAgainstConfigXML({"MakePizza", "1"}, fileContent);
    bool expectedValue{true};
    EXPECT_EQ(returnedValue, expectedValue);
}

TEST(Interpreter, GivenActionParamsAndFileContentWhenvalidateActionParamsAgainstConfigXMLMethodIsCalledWithNonMatchinArgThenExpectFalse){
    Interpreter interpreter;
    std::string fileContent = R"(<LIDEC><function name="MakePizza" paramsTypes="int"></function></LIDEC>)";
    auto returnedValue = interpreter.validateActionParamsAgainstConfigXML({"MakePizza"}, fileContent);
    auto expectedValue = false;
    EXPECT_EQ(returnedValue, expectedValue);
}
