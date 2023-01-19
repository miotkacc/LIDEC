#include "ActionParams.hpp"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <optional>
#include <queue>
#include <condition_variable>
#include <mutex>


struct Interpreter{
    bool validateActionParamsAgainstConfigXML(ActionParams ActionParams, std::string configXML);
    bool validateParamsAgainstParams(std::vector<std::string> argsVals, std::vector<std::string> argTypesVector);
    void startThread(std::queue<ActionParams>& que, std::condition_variable& cv, std::mutex& m);
    void addActionParams(ActionParams actionParams, std::queue<ActionParams>& que, std::mutex& m, std::condition_variable& cv);
};