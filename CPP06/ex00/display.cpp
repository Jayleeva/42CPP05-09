#include "utils.hpp"

void    display_pseudo(std::string litteral)
{
    float   pseudof;
    double  pseudo;

    std::cout << "char : impossible" << std::endl;
    std::cout << "int : impossible" << std::endl;

    if (litteral == "+inf" || litteral == "+inff")
    {
        pseudof = std::numeric_limits<float>::infinity();
        pseudo = std::numeric_limits<double>::infinity();
        std::cout << "float : " << "+" << pseudof << "f" << std::endl;
        std::cout << "double : " << "+" << pseudo << std::endl;
        return ;
    }
    if (litteral == "nan" || litteral == "nanf")
    {
        pseudof = nanf(litteral.c_str());
        pseudo = nan(litteral.c_str());
    }
    else if (litteral == "-inf" || litteral == "-inff")
    {
        pseudof = -std::numeric_limits<float>::infinity();
        pseudo = -std::numeric_limits<double>::infinity();
    }
    std::cout << "float : " << pseudof << "f" << std::endl;
    std::cout << "double : " << pseudo << std::endl;
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