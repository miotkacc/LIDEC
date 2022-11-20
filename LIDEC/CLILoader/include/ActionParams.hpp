#pragma once

#include <string>
#include <vector>
#include <iostream>


struct ActionParams{
    std::string action{};
    std::vector<std::string> params{};
    bool operator==(const ActionParams& actionParams) const {
        return action == actionParams.action and params == actionParams.params; 
    }
};

std::ostream& operator<<(std::ostream& o, const ActionParams& actionParams);
