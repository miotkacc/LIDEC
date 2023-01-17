#pragma once
#include <string>
#include <filesystem>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "ActionParams.hpp"

struct Dispatcher{
    Dispatcher(std::function<void(std::filesystem::path)> cat, std::function<void(std::string)> echoUp, std::function<void(std::vector<int>)> sum)
    :cat(cat), echoUp(echoUp), sum(sum), stop{false}{};
    void registerAction(const ActionParams);
    void passCommandsToExecutors();
    void startThread();
    std::vector<ActionParams> registeredActions;
    std::function<void(std::filesystem::path)> cat;
    std::function<void(std::string)> echoUp;
    std::function<void(std::vector<int>)> sum;
    void startThread(std::queue<ActionParams>& que, std::condition_variable& cv, std::mutex& m);
private:
    void threadTask(std::queue<ActionParams>& que, std::condition_variable& cv, std::mutex& m);
    bool stop;
    std::thread t;
};
