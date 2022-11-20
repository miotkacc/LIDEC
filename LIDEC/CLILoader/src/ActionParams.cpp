#include "ActionParams.hpp"

std::ostream& operator<<(std::ostream& o, const ActionParams& actionParams)
{
    o<<"----------ActionParams---------------\n";
    o<<"action is "<<actionParams.action<<"\n";
    for(const auto& param: actionParams.params){
        o<<"param "<<param<<"\n";
    }
    o<<"-------------------------------------\n";
    return o;
}