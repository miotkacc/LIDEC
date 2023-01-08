#include "XMLLoader.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex>
#include <fstream>

std::optional<std::string> XMLLoader::getProp(const xmlNode *node, std::string wantedPropName)
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

xmlNode *XMLLoader::getFirstChild(xmlDocPtr docPtr)
{
    auto childrenNode = docPtr->xmlChildrenNode;
    if (childrenNode == nullptr)
    {
        return nullptr;
    }
    return childrenNode->xmlChildrenNode;
}

std::vector<std::string> XMLLoader::stringToVector(std::string inArgs)
{
    auto regExp = std::regex("([^ ]+)");
    const std::sregex_iterator end{};
    std::vector<std::string> vectorOfStrings;
    for (std::sregex_iterator s{inArgs.cbegin(), inArgs.cend(), regExp}; s != end; s++)
    {
        vectorOfStrings.push_back((*s)[0].str());
    }
    return vectorOfStrings;
}

std::string XMLLoader::getFileContent(std::filesystem::path path)
{
    std::string fileContent;
    std::fstream f;
    f.open(path, std::ios::in);
    if (f.is_open())
    {
        std::getline(f, fileContent, '\0');
    }
    else
    {
        std::cout << "File not opened" << std::endl;
    }
    f.close();
    return fileContent;
}

std::vector<ActionParams> XMLLoader::parseXMLString(std::string in_str)
{
    auto pointer_uchar = (unsigned char *)in_str.c_str();
    xmlDocPtr doc = xmlParseDoc(pointer_uchar);

    auto parentNode = doc->xmlChildrenNode;
    if(parentNode == nullptr)
    {
        std::cerr<<__FILE__<<__LINE__<<"parentNode == nullptr"<<std::endl;
        return {};
    }

    auto childrenNode = parentNode->xmlChildrenNode;
    if(childrenNode == nullptr)
    {
        std::cerr<<__FILE__<<__LINE__<<"childrenNode == nullptr"<<std::endl;
        return {};
    }

    std::vector<ActionParams> actionParamsVector;

    while (!xmlStrcmp(childrenNode->name, (const xmlChar *)"exec"))
    {
        ActionParams actionParams{};
        auto actionPtr = xmlGetProp(childrenNode, (const xmlChar *)"action");
        if (actionPtr != nullptr)
        {
            std::string action((const char *)actionPtr);
            actionParams.action = action;
        }else{
            std::cerr<<__FILE__<<__LINE__<<"no action"<<std::endl;
            continue;
        }
        auto paramsPtr = xmlGetProp(childrenNode, (const xmlChar *)"params");
        if (paramsPtr != nullptr)
        {
            std::string params((const char *)paramsPtr);
            actionParams.params = params;
        }else{
            std::cerr<<__FILE__<<__LINE__<<"no params"<<std::endl;
            continue;
        }
        actionParamsVector.push_back(actionParams);
        childrenNode = childrenNode->next;
        if(childrenNode == nullptr)
            break;
    }

    xmlFreeDoc(doc);
    return actionParamsVector;
}
