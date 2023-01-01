#include "CLILoader.hpp"

#include <iostream>
#include <regex>


void CLILoader::showExampleInput(){
    std::cout<<"please give me input like "<<std::endl;
    std::cout<<"action param1 param2 param3 param4"<<std::endl;
    std::cout<<"MakeSoup water potato onion oil"<<std::endl;
}

std::string CLILoader::capture(){
    std::string userProvidedStr{};
    std::cin>>userProvidedStr;
    return userProvidedStr;
}

ActionParams CLILoader::parse(std::string someInput){
    auto regExp = std::regex("([a-zA-Z0-9]+)");
    const std::sregex_iterator end{};
    ActionParams actionParams{};
    bool firstElementFound{};
    for(std::sregex_iterator s{someInput.cbegin(), someInput.cend(), regExp}; s!=end;s++)
    {
        if(not firstElementFound){
            actionParams.action = (*s)[0].str();
            firstElementFound = true;
        }else{
            actionParams.params += ((*s)[0].str());
            actionParams.params += " ";
        }
    }
    if(actionParams.params.length() != 0){
        actionParams.params.pop_back();
    }
    return actionParams;
}
