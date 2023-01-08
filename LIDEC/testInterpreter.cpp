#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "Interpreter.hpp"


TEST(Interpreter, GivenActionParamsAndFileContentWhenvalidateActionParamsAgainstConfigXMLMethodIsCalledThenExpectTrue){
    Interpreter interpreter;
    std::string fileContent = R"(<LIDEC><function name="MakePizza" paramsTypes="ints"></function></LIDEC>)";
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

TEST(Interpreter, GivenActionParamsAndFileContentWith3IntsWhenvalidateActionParamsAgainstConfigXMLMethodIsCalledThenExpectTrue){
    Interpreter interpreter;
    std::string fileContent = R"(<LIDEC><function name="MakePizza" paramsTypes="ints"></function></LIDEC>)";
    auto returnedValue = interpreter.validateActionParamsAgainstConfigXML({"MakePizza", "1 1 1"}, fileContent);
    auto expectedValue = true;
    EXPECT_EQ(returnedValue, expectedValue);
}