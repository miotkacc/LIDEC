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
    dispatcher.passCommandsToExecutors();
    std::queue<ActionParams> que; 
    std::condition_variable cv; 
    std::mutex m;
    dispatcher.startThread(que, cv, m);
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds{1});
        std::lock_guard<std::mutex> lg(m);
        que.push(ActionParams{"sum", "1 2 3"});
        cv.notify_one();
    }
    return 0;
}