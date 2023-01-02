#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "XMLLoader.hpp"

TEST(XMLLoader, GivenXMLLoaderWhengetFileContentIsCalledThenExpectFileContentOutput)
{
    XMLLoader xMLLoader;

    auto output = xMLLoader.getFileContent("dd.txt");

    auto expectedOutput = "<action>MakeSoup</action>";

    EXPECT_EQ(output, expectedOutput);
}

TEST(XMLLoader, GivenXMLLoaderWhenparseXMLStringIsCalledThenExpectParsedOutput)
{
    auto xMLLoader = XMLLoader{};
    
    auto actionParams = xMLLoader.parseXMLString(R"(<LIDEC><exec action="Make Pizza" params="1 Onion"></exec></LIDEC>)");

    auto expectedOutput = ActionParams{"Make Pizza", "1 Onion"};

    EXPECT_EQ(actionParams, expectedOutput);
}

TEST(XMLLoader, GivenStringWhenstringToVectorMethodIsCalledWithStringSeparatedWithSpacesExpectVectorOfString)
{
    std::vector<std::string> expectedVectorOfStrings{"1", "2", "potatoes"};
    auto returnedVectorOfStrings = XMLLoader::stringToVector("1 2 potatoes");
    EXPECT_EQ(expectedVectorOfStrings, returnedVectorOfStrings);
}