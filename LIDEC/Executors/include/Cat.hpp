#pragma once
#include <filesystem>

namespace Executors{
    struct Cat{
        void operator()(std::filesystem::path);
    };
}