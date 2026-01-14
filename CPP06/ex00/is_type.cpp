#include "utils.hpp"

int  is_char(char *c, std::string litteral)
{
    int len = litteral.length();

    if (len == 4)
    {
        if (litteral[0] == '\'' && litteral[2] == '\'')
        {
            *c = litteral[1];
            return (1);
        }
    }
    if (len == 5)
    {
        if (litteral[0] == '\'' && litteral[1] == '\\' && litteral[3] == '\'')
        {
            *c = litteral[2];
            return (1);
        }
    }
    return (0);
}

int  is_int(int *i, std::string litteral)
{
    int len = litteral.length();

    if (is_over_borders(litteral, len, 0))
        return (0);
    for (int j = 0; j < len; j++)
    {
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (!isdigit(litteral[j]))
            return (0);
    }
    *i = stoi(litteral);
    return (1);
}


int is_float(float *f, std::string litteral)
{
    int     len = litteral.length();
    int     dot = 0;

    // + check les min max?
    // gérer cas nanf et inff++ inff--
    for (int j = 0; j < len; j++)
    {
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            if (litteral[j + 1] && !isdigit(litteral[j + 1]))
                return (0);
        }
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (j != len && !isdigit(litteral[j]) && litteral[j] != '.')
            return (0);
        if (j == len && litteral[j] != 'f')
            return (0);
    }
    *f = stof(litteral);
    return (1);
}

int is_double(double *d, std::string litteral)
{
    int     len = litteral.length();
    int     dot = 0;

    // + check les min max?
    // gérer cas nan et inf++ inf--
    for (int j = 0; j < len; j++)
    {
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            if (litteral[j + 1] && !isdigit(litteral[j + 1]))
                return (0);
        }
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (j != len && !isdigit(litteral[j]) && litteral[j] != '.')
            return (0);
    }
    *d = stod(litteral);
    return (1);
}