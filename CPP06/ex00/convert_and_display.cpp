#include "utils.hpp"

void convert_and_display_from_char(char c)
{
    bool    tolerance = std::fabs(c - static_cast<char>(c)) < 0.0000000000001;

    display_char(c);
    display_int(static_cast<int>(c));
    display_float(static_cast<float>(c), tolerance);
    display_double(static_cast<double>(c), tolerance);
}

void convert_and_display_from_int(int i)
{
    bool    tolerance = std::fabs(i - static_cast<int>(i)) < 0.0000000000001;

    if (i < 0 || i > 127)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(static_cast<char>(i));
    display_int(i);
    display_float(static_cast<float>(i), tolerance);
    display_double(static_cast<double>(i), tolerance);
}

void convert_and_display_from_float(float f)
{
    bool    tolerance = std::fabs(f - static_cast<int>(f)) < 0.0000000000001;

    if (f < 0.0f || f > 127.0f)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(static_cast<char>(f));
    if (f < MIN_INT || f > MAX_INT || static_cast<int>(f) == -2147483648)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(static_cast<int>(f));
    display_float(f, tolerance);
    if (f != 0 && (f < MIN_DOUBLE || f > MAX_DOUBLE))
        std::cout << "double : impossible" << std::endl;
    else
        display_double(static_cast<double>(f), tolerance);
}

void convert_and_display_from_double(double d)
{
    bool    tolerance = std::fabs(d - static_cast<int>(d)) < 0.0000000000001;

    if (d < 0.0 || d > 127.0)
        std::cout << "char : impossible" << std::endl;
    else
        display_char(static_cast<char>(d));
    if (d < MIN_INT || d > MAX_INT)
        std::cout << "int : impossible" << std::endl;
    else
        display_int(static_cast<int>(d));
    if (d != 0 && (d < MIN_FLOAT || d > MAX_FLOAT))
        std::cout << "float : impossible" << std::endl;
    else
        display_float(static_cast<float>(d), tolerance);
    display_double(d, tolerance);
}
