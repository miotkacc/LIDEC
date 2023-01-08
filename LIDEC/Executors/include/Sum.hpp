#pragma once
#include <initializer_list>
#include <numeric>
#include <vector>


namespace Executors{
    struct Sum{
        void operator()(std::vector<int>);
    };
}
