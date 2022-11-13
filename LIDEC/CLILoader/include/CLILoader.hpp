#include <string>

#include "ActionParams.hpp"

class CLILoader{
    public:
        std::string capture();
        void showExampleInput();
        [[nodiscard]]
        ActionParams parse(std::string);
};
