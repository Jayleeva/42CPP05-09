#include "utils.hpp"

int ft_stoi(std::string litteral)
{
    long    l;
    int     len = litteral.length();
    int     start = 0;

    if (litteral[len -1] == 'f')
        throw UnexpectedCharException();
    if (litteral[0] == '+' || litteral[0] == '-')
        start = 1;
    if (litteral[0] == '.' || (start == 1 && litteral[start] == '.'))
        throw UnexpectedCharException();
    for (int j = start; j < len; j++)
    {
        if (!isdigit(litteral[j]))
            throw UnexpectedCharException();
    }
	l = atol(litteral.c_str());
    if (l < MIN_INT || l > MAX_INT)
        throw OverMinMaxException();
    return (int(l));
}

float   ft_stof(std::string litteral)
{
    float       f;
    int         len = litteral.length();
    int         dot = 0;
    int         start = 0;

    if (litteral[0] == '+' || litteral[0] == '-')
        start = 1;
    if (litteral[0] == '.' || (start == 1 && litteral[start] == '.'))
        throw UnexpectedCharException();
    for (int j = start; j < len; j++)
    {
        if (j != start && litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                throw UnexpectedCharException();
            if (litteral[j + 1] == 0 || !isdigit(litteral[j + 1]))
                throw UnexpectedCharException();
        }
        if ((!isdigit(litteral[j]) && litteral[j] != '.' && litteral[j] != 'f'))
            throw UnexpectedCharException();
    }
    if (dot == 1 && litteral[len -1] != 'f')
        throw UnexpectedCharException();
    f = atof(litteral.c_str());
	if (f < MIN_FLOAT || f > MAX_FLOAT)
    {
        std::cout << f << std::endl;
        throw OverMinMaxException();
    }
    return (f);
}

double  ft_stod(std::string litteral)
{
    double      d;
    int         len = litteral.length();
    int         dot = 0;
    int         start = 0;

    if (litteral[len -1] == 'f')
        throw UnexpectedCharException();
    if (litteral[0] == '+' || litteral[0] == '-')
        start = 1;
    if (litteral[0] == '.' || (start == 1 && litteral[start] == '.'))
        throw UnexpectedCharException();
    for (int j = start; j < len; j++)
    {
        if (j != start && litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                throw UnexpectedCharException();
            if (litteral[j + 1] == 0 || !isdigit(litteral[j + 1]))
                throw UnexpectedCharException();
        }
        if ((!isdigit(litteral[j]) && litteral[j] != '.'))
            throw UnexpectedCharException();
    }
    d = atof(litteral.c_str());
    if (d < MIN_DOUBLE || d > MAX_DOUBLE)
        throw OverMinMaxException();
    return (d);
}