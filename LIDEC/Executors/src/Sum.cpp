#include "Sum.hpp"
#include <iostream>


namespace Executors{
    void Sum::operator()(std::initializer_list<int> args){
        auto val = std::accumulate(args.begin(), args.end(), int(0));
        std::cout<<"Sum result "<<val<<std::endl;
    }
}
