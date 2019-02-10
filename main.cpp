#include <iostream>
#include <type_traits>

// https://baptiste-wicht.com/posts/2015/07/simulate-static_if-with-c11c14.html
// https://lists.boost.org/Archives/boost/2014/08/216607.php

template <bool B, typename T = void>
using enable_if_t = typename std::enable_if<B, T>::type;


template<typename T, enable_if_t<!std::is_same<std::string, T>::value, int> = 42>
void decrement_kindof(T &value)
{
    --value;
}

template<typename T, enable_if_t<std::is_same<std::string, T>::value, int> = 42>
void decrement_kindof(T &value)
{
    value.pop_back();
}

int main()
{
    auto two_int = 2;
    decrement_kindof(two_int);
    std::cout << two_int << std::endl;
    std::string two_string{"two"};
    decrement_kindof(two_string);
    std::cout << two_string << std::endl;
    return 0;
}