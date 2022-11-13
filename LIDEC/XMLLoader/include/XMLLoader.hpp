#include <filesystem>

#include "ActionParams.hpp"

class XMLLoader{
public:
    std::string getFileContent(std::filesystem::path);
    //std::string getXMLTree(std::string)
    //ActionParams ParseXML();
};