#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"


template<typename T>
void    printElement(T const &element)
{
    std::cout << element << std::endl;
}

//const_cast<int&>(ref) = 3; 
//void (*f)(T &) // F f
template<typename T, typename F>
void    iter(T *array, const int len, F f)
{
    for (int i = 0; i < len; i ++)
    {
        f(array[i]);
    }
}

#endif