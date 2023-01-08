#include "EchoUp.hpp"
#include <iostream>

namespace Executors{
    void EchoUp::operator()(std::string inString){
        std::string upString;
        std::transform(inString.begin(), inString.end(), std::back_inserter(upString), [](char& c){return std::toupper(c);});
        std::cout<<upString;
    }
}