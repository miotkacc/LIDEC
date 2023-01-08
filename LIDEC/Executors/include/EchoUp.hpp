#pragma once

#include <string>


namespace Executors{
    struct EchoUp{
        void operator()(std::string);
    };
}