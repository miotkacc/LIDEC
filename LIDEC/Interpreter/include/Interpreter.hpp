#include "ActionParams.hpp"

struct Interpreter{
    std::vector<std::string> stringToVector(std::string inArgs);
    void validateAgainstConfig(ActionParams ActionParams, std::string configXML);
};