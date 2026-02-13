#include "whatever.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n***\nTwo ints have been put in an array. Max and min are checked, then the values are swaped, and max and min are checked again.\n-------" << std::endl;

        int array[2];
        int a = 4;
        int b = 2;

        array[0] = a;
        array[1] = b;
        std::cout << "between the first int (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;

        ::swap(array[0], array[1]);

        std::cout << "between the first int (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 1:\n***\nSame than before, but with char.\n-------" << std::endl;

        char array[2];
        char a = 'a';
        char b = 'z';

        array[0] = a;
        array[1] = b;
        std::cout << "between the first char (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;

        ::swap(array[0], array[1]);

        std::cout << "between the first char (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 2:\n***\nSame than before, but with float.\n-------" << std::endl;

        float array[2];
        float a = 0.001;
        float b = 0.01;

        array[0] = a;
        array[1] = b;
        std::cout << "between the first float (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;

        ::swap(array[0], array[1]);

        std::cout << "between the first float (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;
        std::cout << "=============" << std::endl;
    }
    {
        std::cout << "Main 3:\n***\nSame than before, but with strings.\n-------" << std::endl;

        std::string array[2];
        std::string a = "string 1";
        std::string b = "string 2";

        array[0] = a;
        array[1] = b;
        std::cout << "between the first string (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;

        ::swap(array[0], array[1]);

        std::cout << "between the first string (" << array[0] << ") and the second one (" << array[1] << ")," << std::endl;
        std::cout << "- max is : " << ::max(a, b) << std::endl;
        std::cout << "- min is : " << ::min(a, b) << std::endl;
        std::cout << "=============" << std::endl;
    }
    return (0);
}