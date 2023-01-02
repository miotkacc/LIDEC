#include <filesystem>

#include "ActionParams.hpp"
#include <vector>
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <optional>


class XMLLoader{
public:
    static std::string getFileContent(std::filesystem::path);
    static ActionParams parseXMLString(std::string in_str);
    static std::vector<std::string> stringToVector(std::string inArgs);
    static std::optional<std::string> getProp(const xmlNode *node, std::string);
    static xmlNode* getFirstChild(xmlDocPtr);
};
