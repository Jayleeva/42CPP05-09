#include "utils.hpp"

int  is_char(char *c, std::string litteral)
{
    char    array[litteral.length() + 1];

    for (int j = 0; j < sizeof(array); j++) 
        array[j] = str[j];

    if (sizeof(array) == 4)
    {
        if (array[0] == '\'' && array[2] == '\'')
        {
            c = array[1];
            return (1);
        }
    }
    if (sizeof(array) == 5)
    {
        if (array[0] == '\'' && array[1] == '\\' && array[3] == '\'')
        {
            c = array[2];
            return (1);
        }
    }
    return (0);
}

int  is_int(int *i, std::string litteral)
{
    int len = litteral.length();

    is_over_int_borders(litteral);
    for (int j = 0; j < len; j++)
    {
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (!isdigit(litteral[j]))
            return (0);
    }
    i = litteral; // developper?
    return (1);
}

int is_float(float *f, std::string litteral)
{
    int len = litteral.length();
    int dot = 0;

    // + check les min max?
    // gérer cas nanf et inff++ inff--
    for (int j = 0; j < len; j++)
    {
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            if litteral[j + 1] && !isdigit(litteral[j + 1])
                return (0);
        }
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (j != len && !isdigit(litteral[j]) && litteral[j] != '.')
            return (0);
        if (j == len && litteral[j] != 'f')
            return (0);
    }
    f = litteral; // developper
    return (1);
}

int is_double(double *d, std::string litteral)
{
    int len = litteral.length();
    int dot = 0;

    // + check les min max?
    // gérer cas nan et inf++ inf--
    for (int j = 0; j < len; j++)
    {
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            if litteral[j + 1] && !isdigit(litteral[j + 1])
                return (0);
        }
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (j != len && !isdigit(litteral[j]) && litteral[j] != '.')
            return (0);
    }
    d = litteral; // developper
    return (1);
}