#include "utils.hpp"

void    display_pseudo(std::string litteral)
{
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
    }
}

void    display_error(std::string litteral)
{
    std::cout << "Error: " << litteral << " is not a valid litteral." << std::endl;
}

void    display_char(char c)
{
    if (c < 33 || c == 127)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char : " << "'" << c << "'" << std::endl;
}

void    display_int(int i)
{
    std::cout << "int : " << i << std::endl;
}

void    display_float(float f, bool tolerance)
{
    std::cout << "float : " <<  f << (tolerance ? ".0f" : "f") << std::endl;
}

void    display_double(double d, bool tolerance)
{
    std::cout << "double : " <<  d << (tolerance ? ".0" : "") << std::endl;
}