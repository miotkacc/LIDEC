#include "Cat.hpp"
#include <fstream>
#include <iostream>


namespace Executors{
    void Cat::operator()(std::filesystem::path path){
        std::string fileContent;
        std::fstream f;
        f.open(path, std::ios::in);
        if (f.is_open())
        {
            std::getline(f, fileContent, '\0');
        }
        else
        {
            std::cout << "File not opened" << std::endl;
        }
        f.close();
        std::cout<<fileContent;
    }   
}
