#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <cmath>
# include <limits>

# define MIN_INT std::numeric_limits<int>::min() //-2147483648
# define MAX_INT std::numeric_limits<int>::max() //2147483647
# define MIN_FLOAT std::numeric_limits<float>::min() //-3.40282e+38
# define MAX_FLOAT std::numeric_limits<float>::max() //3.40282e+38
# define MIN_DOUBLE std::numeric_limits<double>::min() //-1.79769e+308
# define MAX_DOUBLE std::numeric_limits<double>::max() //1.79769e+308


void    	display_error(std::string litteral);
void    	display_pseudo(std::string litteral);
void        display_char(char c);
void        display_int(int i);
void        display_int(int i);
void        display_float(float f, bool tolerance);
void        display_double(double d, bool tolerance);

int 		ft_stoi(std::string litteral);
float   	ft_stof(std::string litteral);
double  	ft_stod(std::string litteral);

int         is_char(char *c, std::string litteral);
int         char_to_int(char litteral);
float       char_to_float(char litteral);
double      char_to_double(char litteral);

int         is_int(int *i, std::string litteral);
char        int_to_char(int litteral);
float       int_to_float(int litteral);
double      int_to_double(int litteral);

int         is_float(float *f, std::string litteral);
char        float_to_char(float litteral);
int         float_to_int(float litteral);
double      float_to_double(float litteral);

int         is_double(double *d, std::string litteral);
char        double_to_char(double litteral);
int         double_to_int(double litteral);
float       double_to_float(double litteral);

void        convert_and_display_from_char(char c);
void        convert_and_display_from_int(int i);
void        convert_and_display_from_float(float f);
void        convert_and_display_from_double(double d);

class OverMinMaxException : public std::exception
{
    public:
        virtual const char *what() const throw()
        {
            return ("Exception : Value is over min or max.");
        }
};

class UnexpectedCharException : public std::exception
{
    public:
        virtual const char *what() const throw()
        {
            return ("Exception : Unexpected character.");
        }
};

#endif