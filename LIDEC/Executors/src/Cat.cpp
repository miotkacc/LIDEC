#include "Cat.hpp"
#include <fstream>
#include <iostream>


namespace Executors{
    void Cat::operator()(std::filesystem::path path){
        std::string fileContent;
        std::fstream f;
        f.open(path, std::ios::in);
        f>>fileContent;
        f.close();
        std::cout<<fileContent;
    }   
}
