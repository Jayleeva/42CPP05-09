#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

template<typename T>
void swap(T &a, T &b)
{
    T   tmp = a;

    a = b;
    b = tmp;
    std::cout << YELLOW << "[DEBUG] : Elements have been swapped!" << DEFAULT << std::endl;
}

template<typename T>
const T min(T a, T b)
{
    return (b > a ? a : b);
}

template<typename T>
const T max(T a, T b)
{
    return (b < a ? a : b);
}

#endif