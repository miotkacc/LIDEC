#include "Interpreter.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex>
#include <typeinfo>
#include <ranges>
#include <filesystem>

std::optional<std::string> Interpreter::getProp(const xmlNode *node, std::string wantedPropName)
{
    auto propPtr = xmlGetProp(node, (const xmlChar *)wantedPropName.c_str());
    if (propPtr != nullptr)
    {
        return std::string((const char *)propPtr);
    }
    else
    {
        return std::nullopt;
    }
}

xmlNode* Interpreter::getFirstChild(xmlDocPtr docPtr){
    auto childrenNode = docPtr->xmlChildrenNode;
    if (childrenNode == nullptr)
    {
        return nullptr;
    }
    return childrenNode->xmlChildrenNode;
}

std::vector<std::string> Interpreter::stringToVector(std::string inArgs)
{
    auto regExp = std::regex("([a-zA-Z0-9]+)");
    const std::sregex_iterator end{};
    std::vector<std::string> vectorOfStrings;
    for (std::sregex_iterator s{inArgs.cbegin(), inArgs.cend(), regExp}; s != end; s++)
    {
        vectorOfStrings.push_back((*s)[0].str());
    }
    return vectorOfStrings;
}

bool Interpreter::validateParamsAgainstParams(std::vector<std::string> argsVals, std::vector<std::string> argTypesVector){
    if (argsVals.size() != argTypesVector.size())
    {
        return false;
    }
    auto numberOfElements = argsVals.size();
    for (decltype(numberOfElements) elementNumber = 0; elementNumber < numberOfElements; elementNumber++)
    {
        auto argType = argTypesVector[elementNumber];
        auto arg = argsVals[elementNumber];
        if (argType == "string")
        {
            continue;
        }
        if (argType == "int")
        {
            try
            {
                auto val = std::stoi(arg);
                continue;
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
                return false;
            }
        }
        if (argType == "filename")
        {
            try
            {
                auto val = std::filesystem::path(arg);
                continue;
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
                return false;
            }
        }
        return false;
    }
    return true;
}

bool Interpreter::validateActionParamsAgainstConfigXML(ActionParams actionParams, std::string configXML)
{
    auto pointer_uchar = (unsigned char *)configXML.c_str();
    xmlDocPtr doc; /* the resulting document tree */
    doc = xmlParseDoc(pointer_uchar);

    auto childrenNode = getFirstChild(doc);
    if (childrenNode == nullptr)
    {
        return false;
    }
    for (auto actualNode = childrenNode; actualNode != nullptr; actualNode = actualNode->next)
    {
        if (std::basic_string<unsigned char>(actualNode->name) ==
            std::basic_string<unsigned char>((unsigned char *)"function"))
        {
            auto name = getProp(actualNode, "name");
            if (name and name == actionParams.action)
            {
                auto argTypes = getProp(actualNode, "paramsTypes");
                if (argTypes)
                {
                    auto args = stringToVector(actionParams.params);
                    auto argTypesVector = stringToVector(*argTypes);
                    auto recognizedParam = validateParamsAgainstParams(args, argTypesVector);
                    if(recognizedParam)
                        return true;
                }
            }
        }
    }
    xmlFreeDoc(doc);
    return false;
}
