#include "CLILoader.hpp"
#include "XMLLoader.hpp"
#include "ActionParams.hpp"
#include "Interpreter.hpp"
#include <iostream>
#include "Dispatcher.hpp"
#include "Cat.hpp"
#include "EchoUp.hpp"
#include "Sum.hpp"

using namespace std::literals::string_literals;

int main(){
    CLILoader cLILoader;
    while(1)
    {   
        std::cout<<"Please type echoUp hehe"<<std::endl;
        std::cout<<"or cat ../test.txt"<<std::endl;
        std::cout<<"or sum 1 2 3"<<std::endl;
        std::string userInput;
        std::getline(std::cin, userInput);
        auto a = cLILoader.parse(userInput);
        Interpreter interpreter;
        std::string fileContent = XMLLoader::getFileContent("../config.xml");
        if(not interpreter.validateActionParamsAgainstConfigXML(a, fileContent)){
            return 1;
        }
        Dispatcher dispatcher(Executors::Cat{}, Executors::EchoUp{}, Executors::Sum{});
        dispatcher.registerAction(a);
        dispatcher.passCommandsToExecutors();
    }
    return 0;
}