#include "Interpreter.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex>
#include <typeinfo>
#include <ranges>
#include <filesystem>
#include "XMLLoader.hpp"

bool Interpreter::validateParamsAgainstParams(std::vector<std::string> argsVals, std::vector<std::string> argTypesVector){
    if(argTypesVector.size() == 1 and argTypesVector[0] == "ints"){
        for (auto arg: argsVals)
        {
            std::vector<std::string> ints = XMLLoader::stringToVector(arg);
            for(auto stringInt: ints)
            {
                try
                {
                    auto val = std::stoi(stringInt);
                }
                catch (const std::exception &e)
                {
                    std::cerr<<__FILE__<<":"<<__LINE__<< e.what()<<" in Interpreter during converting string to integer" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

    if (argsVals.size() != argTypesVector.size())
    {
         std::cerr <<__FILE__<<":"<<__LINE__<<"incosistent size of two vectors"<<std::endl;
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
        if (argType == "filename")
        {
            try
            {
                auto val = std::filesystem::path(arg);
                continue;
            }
            catch (const std::exception &e)
            {
                std::cerr<<__FILE__<<":"<<__LINE__ << e.what() << std::endl;
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
        std::cerr<<__FILE__<<":"<<__LINE__<<" problem with xml"<<std::endl;
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
    std::cerr<<__FILE__<<":"<<__LINE__<<" not valid actionParams against config xml"<<std::endl;
    return false;
}

void Interpreter::addActionParams(ActionParams actionParams, std::queue<ActionParams>& que, std::mutex& m, std::condition_variable& cv){
    std::lock_guard lk(m);
    que.push(actionParams);
    cv.notify_one();
}
