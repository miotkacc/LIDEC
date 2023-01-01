#include "XMLLoader.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>

std::string XMLLoader::getFileContent(std::filesystem::path)
{
    return "<action>MakeSoup</action>";
}

ActionParams XMLLoader::parseXMLString(std::string in_str)
{
    
    auto pointer_uchar = (unsigned char*)in_str.c_str(); 
    xmlDocPtr doc; /* the resulting document tree */
    doc = xmlParseDoc(pointer_uchar);
    
    auto childrenNode = doc->xmlChildrenNode;
    if(childrenNode == nullptr){
        return {};
    }
    childrenNode = childrenNode->xmlChildrenNode;
    if(childrenNode == nullptr){
        return {};
    }
    ActionParams actionParams{};
    if(!xmlStrcmp(childrenNode->name, (const xmlChar*)"exec")){
        auto actionPtr = xmlGetProp(childrenNode, (const xmlChar*)"action");
        if(actionPtr != nullptr){
            std::string action((const char*)actionPtr);
            actionParams.action = action;
        }
        auto paramsPtr = xmlGetProp(childrenNode, (const xmlChar*)"params");
        if(paramsPtr != nullptr){
            std::string params((const char*)paramsPtr);
            actionParams.params = params;
        }
    }
    else{
        std::cout<<"instead  action and params in exec node I have node: "<<(unsigned char*)childrenNode->name<<"\n";
    }
    
    xmlFreeDoc(doc);
    return actionParams;
}
