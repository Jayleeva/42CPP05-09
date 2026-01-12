#include "utils.hpp"

void display_double(double d)
{
    std::cout << "double : " << d << std::endl;
}

void display_float(float f)
{
    std::cout << "float : " << f << std::endl;
}

void display_int(int i)
{
    std::cout << "int : " << i << std::endl;
}

void    display_char(char c)
{
    if (c < '!' || c == 127 || c == 129 || c == 141 || c == 143 || c == 144 || c == 157)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char : " << c << std::endl;
}