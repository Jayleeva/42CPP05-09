#include "utils.hpp"

void convert_and_display_from_char(char c)
{
    bool    tolerance = std::fabs(c - static_cast<char>(c)) < 0.0000000000001;

    display_char(c);
    display_int(char_to_int(c));
    display_float(char_to_float(c), tolerance);
    display_double(char_to_double(c), tolerance);
}

void convert_and_display_from_int(int i)
{
    bool    tolerance = std::fabs(i - static_cast<int>(i)) < 0.0000000000001;

    if (i < 0 || i > 127)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(int_to_char(i));
    display_int(i);
    display_float(int_to_float(i), tolerance);
    display_double(int_to_double(i), tolerance);
}

void convert_and_display_from_float(float f)
{
    bool    tolerance = std::fabs(f - static_cast<int>(f)) < 0.0000000000001;

    if (f < 0.0f || f > 127.0f)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(float_to_char(f));
    if (f < MIN_INT || f > MAX_INT)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(float_to_int(f));
    display_float(f, tolerance);
    if (f < MIN_INT || f > MAX_INT)
        std::cout << "double : impossible" << std::endl;
    else
        display_double(float_to_double(f), tolerance);
}

void convert_and_display_from_double(double d)
{
    bool    tolerance = std::fabs(d - static_cast<int>(d)) < 0.0000000000001;

    if (d < 0.0 || d > 127.0)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(double_to_char(d));
    if (d < MIN_INT || d > MAX_INT)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(double_to_int(d));
    if (d < MIN_INT || d > MAX_INT)
        std::cout << "float : impossible" << std::endl;
    else
        display_float(double_to_float(d), tolerance);
    display_double(d, tolerance);
}
