#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <cctype>

void        display_char(char c);
void        display_int(int i);
void        display_int(int i);
void        display_float(float f);
void        display_double(double d);

std::string cpp_substr(std::string s, int start, int end);
float       cpp_ato(std::string s, int sign);
float       getPrecomma(std::string litteral, int k);
float       getPastcomma(std::string litteral, int k, int len);
int         is_over_int_borders(std::string litteral);

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

#endif