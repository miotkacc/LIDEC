#pragma once
#include <initializer_list>
#include <numeric>

namespace Executors{
    struct Sum{
        void operator()(std::initializer_list<int>);
    };
}
