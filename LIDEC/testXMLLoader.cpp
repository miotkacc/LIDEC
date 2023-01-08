#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "XMLLoader.hpp"

TEST(XMLLoader, GivenXMLLoaderWhengetFileContentIsCalledThenExpectFileContentOutput)
{
    auto output = XMLLoader::getFileContent("../test.xml");

    auto expectedOutput = "<action>MakeSoup</action>";

    EXPECT_EQ(output, expectedOutput);
}

TEST(XMLLoader, GivenFilepathAndExistingFileWhengetFileContentMethodIsCalledExpectFilecontent){
    auto result = XMLLoader::getFileContent("../test.txt");
    std::string expectedResult = "a\nb\nc\n1\n2\n3";
    EXPECT_EQ(result, expectedResult);
}

TEST(XMLLoader, GivenXMLLoaderWhenparseXMLStringIsCalledThenExpectParsedOutput)
{
    auto actionParams = XMLLoader::parseXMLString(R"(<LIDEC><exec action="Make Pizza" params="1 Onion"></exec></LIDEC>)");

    std::vector<ActionParams> expectedOutput{ActionParams{"Make Pizza", "1 Onion"}};

    EXPECT_EQ(actionParams, expectedOutput);
}

TEST(XMLLoader, GivenStringWhenstringToVectorMethodIsCalledWithStringSeparatedWithSpacesExpectVectorOfString)
{
    std::vector<std::string> expectedVectorOfStrings{"1", "2", "potatoes"};
    auto returnedVectorOfStrings = XMLLoader::stringToVector("1 2 potatoes");
    EXPECT_EQ(expectedVectorOfStrings, returnedVectorOfStrings);
}
