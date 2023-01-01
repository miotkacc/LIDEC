#include "Interpreter.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <regex>


std::vector<std::string> Interpreter::stringToVector(std::string inArgs){
    auto regExp = std::regex("([a-zA-Z0-9]+)");
    const std::sregex_iterator end{};
    std::vector<std::string> vectorOfStrings;
    for(std::sregex_iterator s{inArgs.cbegin(), inArgs.cend(), regExp}; s!=end;s++)
    {
        vectorOfStrings.push_back((*s)[0].str());
    }
    return vectorOfStrings;
}

void Interpreter::validateAgainstConfig(ActionParams actionParams, std::string configXML){
    auto pointer_uchar = (unsigned char*)configXML.c_str(); 
    xmlDocPtr doc; /* the resulting document tree */
    doc = xmlParseDoc(pointer_uchar);

    auto childrenNode = doc->xmlChildrenNode;
    if(childrenNode == nullptr){
        return;
    }
    childrenNode = childrenNode->xmlChildrenNode;
    if(childrenNode == nullptr){
        return;
    }
    auto actualNode = childrenNode;
    while(actualNode != nullptr){
        if(std::basic_string<unsigned char>(actualNode->name) == 
        std::basic_string<unsigned char>((unsigned char*)"function"))
        {
            auto namePtr = xmlGetProp(childrenNode, (const xmlChar*)"name");
            if(namePtr != nullptr){
                if(std::string((const char*)namePtr) == actionParams.action)
                {
                    
                }
            }
        }
        actualNode = actualNode->next;
    }
    xmlFreeDoc(doc);
}
