#pragma once
#include <string>
#include <filesystem>
#include <functional>
#include "ActionParams.hpp"

struct Dispatcher{
    Dispatcher(std::function<void(std::filesystem::path)> cat, std::function<void(std::string)> echoUp, std::function<void(std::vector<int>)> sum)
    :cat(cat), echoUp(echoUp), sum(sum){};
    void registerAction(const ActionParams);
    void passCommandsToExecutors();
    std::vector<ActionParams> registeredActions;
    std::function<void(std::filesystem::path)> cat;
    std::function<void(std::string)> echoUp;
    std::function<void(std::vector<int>)> sum;
};
