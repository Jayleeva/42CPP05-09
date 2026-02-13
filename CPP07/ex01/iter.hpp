#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"


template<typename T>
void    printArray(T &array)
{
    std::cout << array << std::endl;
}

template<typename T, typename F>
void    iter(T *array, const size_t len, void (*f)(F&))
{
    for (size_t i = 0; i < len; i ++)
    {
        f(array[i]);
    }
}

#endif