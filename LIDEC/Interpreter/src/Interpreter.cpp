#include "Interpreter.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex>
#include <typeinfo>
#include <ranges>
#include <filesystem>
#include "XMLLoader.hpp"

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

    auto childrenNode = XMLLoader::getFirstChild(doc);
    if (childrenNode == nullptr)
    {
        return false;
    }
    for (auto actualNode = childrenNode; actualNode != nullptr; actualNode = actualNode->next)
    {
        if (std::basic_string<unsigned char>(actualNode->name) ==
            std::basic_string<unsigned char>((unsigned char *)"function"))
        {
            auto name = XMLLoader::getProp(actualNode, "name");
            if (name and name == actionParams.action)
            {
                auto argTypes = XMLLoader::getProp(actualNode, "paramsTypes");
                if (argTypes)
                {
                    auto args = XMLLoader::stringToVector(actionParams.params);
                    auto argTypesVector = XMLLoader::stringToVector(*argTypes);
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
