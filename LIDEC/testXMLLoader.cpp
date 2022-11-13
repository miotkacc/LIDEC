#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "XMLLoader.hpp"

TEST(XMLLoader, GivenXMLLoaderWhengetFileContentIsCalledThenExpectFileContentOutput){
    XMLLoader xMLLoader;
    
    auto output = xMLLoader.getFileContent("dd.txt");

    auto expectedOutput = "<action>MakeSoup</action>";

    EXPECT_EQ(output, expectedOutput);
}