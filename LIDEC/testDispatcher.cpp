#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Dispatcher.hpp"

TEST(Dispatcher, testDispatcherConstructor)
{
    auto cat = [](std::filesystem::path p){};
    auto echoUp = [](std::string s){};
    auto sum = [](std::vector<int> x){return 3;};
    Dispatcher dispatcher(cat, echoUp, sum);
}
