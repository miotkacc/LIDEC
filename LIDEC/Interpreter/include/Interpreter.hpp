#include "ActionParams.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <optional>


struct Interpreter{
    bool validateActionParamsAgainstConfigXML(ActionParams ActionParams, std::string configXML);
    bool validateParamsAgainstParams(std::vector<std::string> argsVals, std::vector<std::string> argTypesVector);
};