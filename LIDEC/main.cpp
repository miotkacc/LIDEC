#include "CLILoader.hpp"

using namespace std::literals::string_literals;

int main(){
    CLILoader cLILoader;
    cLILoader.parse("siema tu ff"s);
    cLILoader.parse("siema"s);
    cLILoader.parse("siema tu ff "s);
}