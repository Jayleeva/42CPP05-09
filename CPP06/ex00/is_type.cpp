#include "utils.hpp"

int  is_char(char *c, std::string litteral)
{
    int len = litteral.length();

    if (len == 1)
    {
        if (!isdigit(litteral[0]))
        {
            *c = litteral[0];
            return (1);
        }
    }
    return (0);
}

int  is_int(int *i, std::string litteral)
{
    try
    {
        *i = ft_stoi(litteral);
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}


int is_float(float *f, std::string litteral)
{
    try
    {
        *f = ft_stof(litteral);
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}

int is_double(double *d, std::string litteral)
{
    try
    {
        *d = ft_stod(litteral);
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}