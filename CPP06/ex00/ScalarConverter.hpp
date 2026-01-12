#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include "utils.hpp"

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class ScalarConverter
{
    public:
        static void convert(std::string litteral) = 0;
    
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &original);
        ScalarConverter const &operator=(ScalarConverter const &original);
        ~ScalarConverter();
}

#endif