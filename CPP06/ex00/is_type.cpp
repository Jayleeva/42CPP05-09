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
    int sign = 1;

    if (is_over_int_borders(litteral))
        return (0);
    if (litteral[0] == '-')
        sign = -1;
    for (int j = 0; j < len; j++)
    {
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (!isdigit(litteral[j]))
            return (0);
    }
    if (litteral[0] == '+' || litteral[0] == '-')
        *i = cpp_ato(litteral, 1) * sign;
    else
        *i = cpp_ato(litteral, 0) * sign;
    return (1);
}


int is_float(float *f, std::string litteral)
{
    int     len = litteral.length();
    int     dot = 0;
    int     k = -1;
    int     sign = 1;
    int     zero = 0;
    float   precomma;
    float   pastcomma;

    // + check les min max?
    // gérer cas nanf et inff++ inff--
    for (int j = 0; j < len; j++)
    {
        if (litteral[0] == '-')
            sign = -1;
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            k = j;
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
    litteral = cpp_substr(litteral, 0, len);
    len = litteral.length();
    if (dot == 1)
    {
        zero = len - k;
        precomma = getPrecomma(litteral, k);
        pastcomma = getPastcomma(litteral, k, len) / zero;
        *f = (precomma + pastcomma) * sign;
    }
    else
        *f = cpp_ato(litteral, 0) * sign;
    return (1);
}

int is_double(double *d, std::string litteral)
{
    int     len = litteral.length();
    int     dot = 0;
    int     k = -1;
    int     sign = 1;
    int     zero = 0;
    float   precomma;
    float   pastcomma;

    // + check les min max?
    // gérer cas nan et inf++ inf--
    for (int j = 0; j < len; j++)
    {
        if (litteral[0] == '-')
            sign = -1;
        if (litteral[j] == '.')
        {
            dot ++;
            if (dot > 1)
                return (0);
            k = j;
            if (litteral[j + 1] && !isdigit(litteral[j + 1]))
                return (0);
        }
        if (j != 0 && (litteral[j] == '+' || litteral[j] == '-'))
            return (0);
        if (j != len && !isdigit(litteral[j]) && litteral[j] != '.')
            return (0);
    }
    if (dot == 1)
    {
        zero = len - k;
        precomma = getPrecomma(litteral, k);
        pastcomma = getPastcomma(litteral, k, len) / zero;
        *d = (precomma + pastcomma) * sign;
    }
    else
        *d = cpp_ato(litteral, 0) * sign;
    return (1);
}