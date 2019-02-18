#include <iostream>

// https://baptiste-wicht.com/posts/2015/07/simulate-static_if-with-c11c14.html
// https://lists.boost.org/Archives/boost/2014/08/216607.php

namespace static_if_detail
{

    struct identity
    {
        template<typename T>
        T operator()(T &&x) const
        {
            return std::forward<T>(x);
        }
    };

    template<bool Cond>
    struct statement
    {
        template<typename F>
        void then(const F &f)
        {
            f(identity());
        }

        template<typename F>
        void else_(const F &)
        {}
    };

    template<>
    struct statement<false>
    {
        template<typename F>
        void then(const F &)
        {}

        template<typename F>
        void else_(const F &f)
        {
            f(identity());
        }
    };

} //end of namespace static_if_detail

template<bool Cond, typename F>
static_if_detail::statement<Cond> static_if(F const &f)
{
    std::puts(__PRETTY_FUNCTION__);
    static_if_detail::statement<Cond> if_;
    if_.then(f);
    return if_;
}

template<typename T>
void decrement_kindof(T &value)
{
    static_if<std::is_same<std::string, T>::value>([&](auto f)
                                                   {
                                                       f(value).pop_back();
                                                   }).else_([&](auto f)
                                                            {
                                                                --f(value);
                                                            });
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