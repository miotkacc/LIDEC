#include <string>

#include "ActionParams.hpp"

class CLILoader{
    public:
        std::string capture();
        void showExampleInput();
        ActionParams parse(std::string);
};
