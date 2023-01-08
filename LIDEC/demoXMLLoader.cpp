#include "CLILoader.hpp"
#include "XMLLoader.hpp"
#include "ActionParams.hpp"
#include "Interpreter.hpp"
#include "Dispatcher.hpp"
#include "Cat.hpp"
#include "EchoUp.hpp"
#include "Sum.hpp"

int main()
{
    auto fileContent = XMLLoader::getFileContent("../demoXMLLoader.xml");
    auto actionParamsVector = XMLLoader::parseXMLString(fileContent);
    Interpreter interpreter;
    auto config = XMLLoader::getFileContent("../config.xml");
    Dispatcher dispatcher(Executors::Cat{}, Executors::EchoUp{}, Executors::Sum{});
    for (auto actionParam : actionParamsVector)
    {
        if (interpreter.validateActionParamsAgainstConfigXML(actionParam, config))
        {
            dispatcher.registerAction(actionParam);
        }
    }
    dispatcher.passCommandsToExecutors();
    return 0;
}