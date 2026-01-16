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
    if (c < '!' || c == 127)
        std::cout << "char : Non displayable" << std::endl;
    else
        std::cout << "char : " << c << std::endl;
}

void    display_int(int i)
{
    std::cout << "int : " <<  static_cast<int>(i) << std::endl;
}

void    display_float(float f)
{
    std::cout << "float : " <<  static_cast<float>(f) << 'f' << std::endl;
}

void    display_double(double d)
{
    std::cout << "double : " <<  static_cast<double>(d) << std::endl;
}