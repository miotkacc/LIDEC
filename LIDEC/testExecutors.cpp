#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Sum.hpp"
#include "EchoUp.hpp"
#include "Cat.hpp"


TEST(ExecutorSum, GivenTwoNumbersWhenOperatorFunctionIsCalledExpectNoCrash)
{
    Executors::Sum sum;
    sum({1,2});
}

TEST(ExecutorSum, GivenFilePathWhenOperatorFunctionIsCalledExpectNoCrash)
{
    Executors::Cat cat;
    cat("test.txt");
}