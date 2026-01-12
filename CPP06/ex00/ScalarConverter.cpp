#include "ScaleConverter.hpp"

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

static void ScalarConverter::convert(std::string litteral)
{
    char    c;
    int     i;
    float   f;
    double  d;

    if (is_char(&c, litteral))
    {
        display_char(c);
        i = char_to_int(c);
        display_int(i);
        f = char_to_float(c);
        display_float(f);
        d = char_to_double(c);
        display_double(d);
    }
    else if (is_int(&i, litteral))
    {
        if (i < 0 || i > 255)
            std::cout << "char : impossible" << std::endl;
        else
        {
            c = int_to_char(i);
            display_char(c);
        }
        display_int(i);
        f = int_to_float(i);
        display_float(f);
        d = int_to_double(i);
        display_double(d);
    }
    else if (is_float(&f, litteral))
    {
        if (f < 0.0f || f > 255.0f)
            std::cout << "char : impossible" << std::endl;
        else
        {
            c = float_to_char(f);
            display_char(c);
        }
        if (litteral == "nanf" || litteral == "nan"
            || litteral == "-inff" || litteral == "-inf"
            || litteral == "+inff" || litteral == "+inf"
            || is_over_borders(litteral))
            std::cout << "int : impossible" << std::endl;
        else
        {
            i = float_to_int(f);
            display_int(i);
        }
        display_float(f);
        d = float_to_double(f);
        display_double(d);
    }
    else if (is_double(&d, litteral))
    {
        if (d < 0.0 || d > 255.0)
            std::cout << "char : impossible" << std::endl;
        else
        {
            c = double_to_char(d);
            display_char(c);
        }
        if (litteral == "nanf" || litteral == "nan"
            || litteral == "-inff" || litteral == "-inf"
            || litteral == "+inff" || litteral == "+inf"
            || is_over_borders(litteral))
            std::cout << "int : impossible" << std::endl;
        else
        {
            i = float_to_int(f);
            display_int(i);
        }
        display_int(i);
        f = double_to_float(litteral);
        display_float(f);
        display_double(d);
    }
}