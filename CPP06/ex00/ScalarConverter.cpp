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

static void convert_and_display_from_char(char c)
{
    display_char(c);
    display_int(char_to_int(c));
    display_float(char_to_float(c));
    display_double(char_to_double(c));
}

static void convert_and_display_from_int(int i)
{
    if (i < 0 || i > 127)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(int_to_char(i));
    display_int(i);
    display_float(int_to_float(i));
    display_double(int_to_double(i));
}

static void convert_and_display_from_float(float f)
{
    if (f < 0.0f || f > 127.0f)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(float_to_char(f));
    if (f < MIN_INT || f > MAX_INT)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(float_to_int(f));
    display_float(f);
    if (f < MIN_DOUBLE || f > MAX_DOUBLE)
        std::cout << "double : impossible" << std::endl;
    else
        display_double(float_to_double(f));
}

static void convert_and_display_from_double(double d)
{
    if (d < 0.0 || d > 127.0)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(double_to_char(d));
    if (d < MIN_INT || d > MAX_INT)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(double_to_int(d));
    if (d < MIN_FLOAT || d > MAX_FLOAT)
        std::cout << "float : impossible" << std::endl;
    else
        display_float(double_to_float(d));
    display_double(d);
}

void ScalarConverter::convert(std::string litteral)
{
    char    c;
    int     i;
    float   f;
    double  d;

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
        else if (is_double(&d, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is a double" << DEFAULT << std::endl;
            convert_and_display_from_double(d);
        }
        else if (is_float(&f, litteral))
        {
            std::cout << YELLOW << "[DEBUG] is a float" << DEFAULT << std::endl;
            convert_and_display_from_float(f);
        }
        else
        {
            display_error(litteral);
        }
    }
}