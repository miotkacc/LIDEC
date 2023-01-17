#include <queue>
#include <condition_variable>

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
        else if(registeredAction.action == "echoUp"){
            echoUp(registeredAction.params);
        }
        else if(registeredAction.action == "sum")
        {
            std::vector<int> elements;
            auto arguments = XMLLoader::stringToVector(registeredAction.params);
            elements.reserve(arguments.size());
            std::transform(arguments.begin(), arguments.end(), std::back_inserter(elements), [](std::string inString){return std::stoi(inString);});
            sum(elements);
        }
        else{
            std::cerr<<__FILE__<<__LINE__<<" couldn't match action with executor"<<std::endl;
        }
    }
}

void Dispatcher::startThread(std::queue<ActionParams>& que, std::condition_variable& cv, std::mutex& m)
{
    t = std::thread(&Dispatcher::threadTask, this, std::ref(que), std::ref(cv), std::ref(m));
}

void Dispatcher::threadTask(std::queue<ActionParams>& que, std::condition_variable& cv, std::mutex& m){
    std::unique_lock<std::mutex> lk;
    while(not stop){
        std::lock_guard<std::mutex> lg(m);
        cv.wait(lk, [&stop = this->stop](){return not stop;});
        if(not que.empty()){
            auto params = que.front();
            que.pop();
            registerAction(params);
            passCommandsToExecutors();
        }
    }
};