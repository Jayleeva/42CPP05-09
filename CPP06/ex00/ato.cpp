#include "utils.hpp"

std::string cpp_substr(std::string s, int start, int end)
{
    std::string res;
    int         j = 0;

    for (int i = start; i < end; i++)
        res[j++] = s[i];
    return (res);
}

float    cpp_ato(std::string s, int sign)
{
    float       res = 0;
    int         n = 1;

    for (int i = s.length(); i > sign; i--)
    {
        if (s[i] == '0' && n > 1)
            res *= n;
        else
            res += (s[i] - '0') * n;
        n *= 10;
    }
    return (res);
}


float   getPrecomma(std::string litteral, int k)
{
    float       pre = 0;
    int         sign;
    std::string sub;

    sub = cpp_substr(litteral, 0, k);
    if (sub[0] == '+' || sub[0] == '-')
        sign = 1;
    else
        sign = 0;
    pre += cpp_ato(sub, sign);
    return (pre);
}

float   getPastcomma(std::string litteral, int k, int len)
{
    float       past = 0;
    std::string sub;

    sub = cpp_substr(litteral, k, len);
    int j = 0;
    while (sub[j++] == 0)
        past = 0;
    past += cpp_ato(sub, j);
    return (past);
}
