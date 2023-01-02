#include "Dispatcher.hpp"
#include "XMLLoader.hpp"


void Dispatcher::registerAction(const ActionParams actionParams){
    registeredActions.push_back(actionParams);
}

void Dispatcher::passCommandsToExecutors(){
    for(const auto& registeredAction : registeredActions){
        if(registeredAction.action == "cat"){
            cat(registeredAction.params);
        }
        if(registeredAction.action == "echoUp"){
            echoUp(registeredAction.params);
        }
        if(registeredAction.action == "sum")
        {
            std::vector<int> elements;
            auto arguments = XMLLoader::stringToVector(registeredAction.params);
            elements.reserve(arguments.size());
            std::transform(arguments.begin(), arguments.end(), std::back_inserter(elements), [](std::string inString){return std::stoi(inString);});
            sum(elements);
        }
    }
}
