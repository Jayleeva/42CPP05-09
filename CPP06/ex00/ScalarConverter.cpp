#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    std::cout << YELLOW << "[CONVERTER]: Default constructor called" << DEFAULT << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &original)
{
	std::cout << YELLOW << "[CONVERTER]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

ScalarConverter const &ScalarConverter::operator=(ScalarConverter const &original)
{
    (void)original;
    std::cout << YELLOW << "[CONVERTER]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

ScalarConverter::~ScalarConverter()
{
    std::cout << YELLOW << "[CONVERTER]: Default destructor called" << DEFAULT << std::endl;
}

void ScalarConverter::convert(std::string litteral)
{
    char    c = 0;
    int     i = 0;
    float   f = 0;
    double  d = 0;

    if (litteral == "nanf" || litteral == "nan"
        || litteral == "-inff" || litteral == "-inf"
        || litteral == "+inff" || litteral == "+inf")
        display_pseudo(litteral);
    else
    {
        if (is_char(&c, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is a char" << DEFAULT << std::endl;
            convert_and_display_from_char(c);
        }
        else if (is_int(&i, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is an int" << DEFAULT << std::endl;
            convert_and_display_from_int(i);
        }
        else if (is_float(&f, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is a float" << DEFAULT << std::endl;
            convert_and_display_from_float(f);
        }
        else if (is_double(&d, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is a double" << DEFAULT << std::endl;
            convert_and_display_from_double(d);
        }
        else
        {
            display_error(litteral);
        }
    }
}