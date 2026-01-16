#include "utils.hpp"

int ft_stoi(std::string litteral)
{
    int i;

	i = atol(litteral.c_str());
    return (i);
}

float   ft_stof(std::string litteral)
{
    float   f;
    
    f = atof(litteral.c_str());
    return (f);
}

double  ft_stod(std::string litteral)
{
    double  d;
    d = atof(litteral.c_str());
    return (d);
}