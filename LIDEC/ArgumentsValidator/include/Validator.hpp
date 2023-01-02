#include <functional>

template<typename T> 
struct count_arg;

template<typename R, typename ...Args> 
struct count_arg<std::function<R(Args...)>>
{
    static const size_t value = sizeof...(Args);
};