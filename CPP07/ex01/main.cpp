#include "iter.hpp"

void    int_increment(int &i)
{
    i++;
}

void    float_increment(float &f)
{
    f++;
}

void    char_toupper(char &c)
{
    c -= 32;
}

void    string_toupper(std::string &s)
{
    int i = 0;
    while (s[i])
    {
        char_toupper(s[i]);
        i ++;
    }
}

void    isabovezero(int const &i)
{
    if (i > 0)
        std::cout << i << " is above zero!" << std::endl;
    else
        std::cout << i << " is not above zero..." << std::endl;
}

int main(void)
{
    {
        std::cout << "Main 0:\n***\nShould print the array with each int incremented.\n------" << std::endl;
        int len = 5;
        int array[len] = {12, 23, 34, 45, 56};

        iter(array, len, int_increment);
        //iter(array, len, ::printElement);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 1:\n***\nShould print the array with each float incremented.\n------" << std::endl;
        int len = 5;
        float array[len] = {1.2, 2.3, 3.4, 4.5, 5.6};

        iter(array, len, float_increment);
        //iter(array, len, ::printElement);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 2:\n***\nShould print the array with each char passed in uppercase.\n------" << std::endl;
        int len = 3;
        char array[len] = {'a', 'b', 'c'};

        iter(array, len, char_toupper);
        //iter(array, len, ::printElement);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 3:\n***\nShould print the array with each string passed in uppercase.\n------" << std::endl;
        int len = 3;
        std::string array[len] = {"hello", "my", "friend"};

        iter(array, len, string_toupper);
        //iter(array, len, ::printElement);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 4:\n***\nShould print if each const int of the array is above zero or not.\n------" << std::endl;
        int len = 4;
        int array[len] = {-12, 23, -34, 45};

        iter(array, len, isabovezero);
        //iter(array, len, ::printElement);
        std::cout << "=============" << std::endl;
    }
    return (0);
}