#include <filesystem>

#include "ActionParams.hpp"

class XMLLoader{
    ActionParams ParseXML(std::filesystem::path file);
};