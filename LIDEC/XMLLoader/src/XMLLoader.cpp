#include "XMLLoader.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>

std::string XMLLoader::getFileContent(std::filesystem::path)
{
    return "<action>MakeSoup</action>";
}


ActionParams XMLLoader::parseXMLString(std::string in_str)
{
    ActionParams actionParams{};
    auto pointer_uchar = (unsigned char*)in_str.c_str(); 
    xmlDocPtr doc; /* the resulting document tree */
    doc = xmlParseDoc(pointer_uchar);
    
    auto childrenNode = doc->xmlChildrenNode;
    if(childrenNode == nullptr){
        return actionParams;
    }
    childrenNode = childrenNode->xmlChildrenNode;
    if(childrenNode == nullptr){
        return actionParams;
    }
    if(!xmlStrcmp(childrenNode->name, (const xmlChar*)"Action")){
        auto x = xmlNodeListGetString(doc, childrenNode->xmlChildrenNode, 1);
        std::string action((const char*)x);
        actionParams.action = action;
    }
    else{
        std::cout<<"zamiast ok action mam"<<(unsigned char*)childrenNode->name<<"\n";
    }
    auto actualNode = childrenNode->next;
    while(actualNode != nullptr){
        if(std::basic_string<unsigned char>(actualNode->name) == 
        std::basic_string<unsigned char>((unsigned char*)"Param"))
        {
            std::cout<<"Params ok"<<"\n";
            auto x = xmlNodeListGetString(doc, actualNode->xmlChildrenNode, 1);
            std::string param((const char*)x);
            actionParams.params.push_back(param);
        }
        actualNode = actualNode->next;
    }
    xmlFreeDoc(doc);
    return actionParams;
}