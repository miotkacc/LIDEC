#include <filesystem>

#include "ActionParams.hpp"

class XMLLoader{
public:
    std::string getFileContent(std::filesystem::path);
    ActionParams parseXMLString(std::string in_str);
};
