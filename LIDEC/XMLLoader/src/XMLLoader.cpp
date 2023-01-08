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
    auto regExp = std::regex("([a-zA-Z0-9]+)");
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

ActionParams XMLLoader::parseXMLString(std::string in_str)
{

    auto pointer_uchar = (unsigned char *)in_str.c_str();
    xmlDocPtr doc; /* the resulting document tree */
    doc = xmlParseDoc(pointer_uchar);

    auto childrenNode = doc->xmlChildrenNode;
    if (childrenNode == nullptr)
    {
        return {};
    }
    childrenNode = childrenNode->xmlChildrenNode;
    if (childrenNode == nullptr)
    {
        return {};
    }
    ActionParams actionParams{};
    if (!xmlStrcmp(childrenNode->name, (const xmlChar *)"exec"))
    {
        auto actionPtr = xmlGetProp(childrenNode, (const xmlChar *)"action");
        if (actionPtr != nullptr)
        {
            std::string action((const char *)actionPtr);
            actionParams.action = action;
        }
        auto paramsPtr = xmlGetProp(childrenNode, (const xmlChar *)"params");
        if (paramsPtr != nullptr)
        {
            std::string params((const char *)paramsPtr);
            actionParams.params = params;
        }
    }
    else
    {
        std::cout << "instead  action and params in exec node I have node: " << (unsigned char *)childrenNode->name << "\n";
    }

    xmlFreeDoc(doc);
    return actionParams;
}
