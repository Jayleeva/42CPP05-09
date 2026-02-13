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
        size_t len = 5;
        int array[] = {12, 23, 34, 45, 56};

        ::iter(array, len, &int_increment);
        ::iter(array, len, &::printArray<int>);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 1:\n***\nShould print the array with each float incremented.\n------" << std::endl;
        size_t len = 5;
        float array[] = {1.2, 2.3, 3.4, 4.5, 5.6};

        ::iter(array, len, &float_increment);
        ::iter(array, len, &::printArray<float>);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 2:\n***\nShould print the array with each char passed in uppercase.\n------" << std::endl;
        size_t len = 3;
        char array[] = {'a', 'b', 'c'};

        ::iter(array, len, &char_toupper);
        ::iter(array, len, &::printArray<char>);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 3:\n***\nShould print the array with each string passed in uppercase.\n------" << std::endl;
        size_t len = 3;
        std::string array[] = {"hello", "my", "friend"};

        ::iter(array, len, &string_toupper);
        ::iter(array, len, &::printArray<std::string>);
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 4:\n***\nShould print if each int of the array is above zero or not.\n------" << std::endl;
        size_t len = 4;
        const int array[] = {-12, 23, -34, 45};

        ::iter(array, len, &isabovezero);
        std::cout << "=============" << std::endl;
    }
    return (0);
}