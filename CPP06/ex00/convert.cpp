#include "utils.hpp"

int ft_stoi(std::string litteral)
{
    long    l;

	l = atol(litteral.c_str());
    if (l < MIN_INT || l > MAX_INT)
        throw OverMinMaxException();
    return (int(l));
}

float   ft_stof(std::string litteral)
{
    float   f;
    
    f = atof(litteral.c_str());
	if (f < MIN_FLOAT || f > MAX_FLOAT)
        throw OverMinMaxException();
    return (f);
}

double  ft_stod(std::string litteral)
{
    double  d;

    d = atof(litteral.c_str());
    if (d < MIN_DOUBLE || d > MAX_DOUBLE)
        throw OverMinMaxException();
    return (d);
}