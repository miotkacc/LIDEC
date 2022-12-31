#include "ActionParams.hpp"

std::ostream& operator<<(std::ostream& o, const ActionParams& actionParams)
{
    o<<"----------ActionParams---------------\n";
    o<<"action is "<<actionParams.action<<"\n";
    o<<"param "<<actionParams.params<<"\n";
    
    o<<"-------------------------------------\n";
    return o;
}