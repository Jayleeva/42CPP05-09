#include "utils.hpp"

char *cpp_substr(const char *s, int start, int end)
{
    char res[end - start + 1];
    int         j = 0;

    for (int i = start; i < end; i++)
        res[j++] = s[i];
    return (res);
}

void    display_pseudo(std::string litteral)
{
    char *tmp;

    std::cout << "char : impossible" << std::endl;
    std::cout << "int : impossible" << std::endl;
    if (litteral == "nan" || litteral == "-inf" || litteral == "+inf")
    {
        std::cout << "float : " << litteral << 'f' << std::endl;
        std::cout << "double : " << litteral << std::endl;
    }
    else
    {
        std::cout << "float : " << litteral << std::endl;
        std::cout << "double : ";
        if (litteral == "nanf")
            std::cout << "nan" << std::endl;
        else if (litteral == "-inff")
            std::cout << "-inf" << std::endl;
        else if (litteral == "+inff")
            std::cout << "+inf" << std::endl;
        tmp = cpp_substr(litteral.c_str(), 0, litteral.length() -1);
        std::cout << "double : " << tmp << std::endl;
    }
}

void    display_char(char c)
{
    if (c < '!' || c == 127)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char : " << c << std::endl;
}

void    display_int(int i)
{
    std::cout << "int : " << i << std::endl;
}

void    display_float(float f)
{
    std::cout << "float : " << f << std::endl;
}

void    display_double(double d)
{
    std::cout << "double : " << d << std::endl;
}