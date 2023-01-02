#include "CLILoader.hpp"
#include "XMLLoader.hpp"
#include "ActionParams.hpp"

using namespace std::literals::string_literals;

int main(){
    CLILoader cLILoader;
    auto a = cLILoader.parse("siema tu ff"s);
    auto b = cLILoader.parse("siema"s);
    auto c = cLILoader.parse("siema tu ff "s);
    auto r = XMLLoader();
    auto ap = r.parseXMLString(R"(<LIDEC><Action>Make Pizza</Action><Param>1</Param><Param>withOnion</Param></LIDEC>)");
    std::cout<<ap<<std::endl;
    std::cout<<__cplusplus<<std::endl;
    return 0;
}