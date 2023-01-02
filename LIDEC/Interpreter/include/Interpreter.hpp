#include "ActionParams.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <optional>


struct Interpreter{
    std::vector<std::string> stringToVector(std::string inArgs);
    bool validateActionParamsAgainstConfigXML(ActionParams ActionParams, std::string configXML);
    bool validateParamsAgainstParams(std::vector<std::string> argsVals, std::vector<std::string> argTypesVector);
    std::optional<std::string> getProp(const xmlNode *node, std::string);
    xmlNode* getFirstChild(xmlDocPtr);
};