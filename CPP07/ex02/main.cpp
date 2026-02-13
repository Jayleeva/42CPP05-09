#include "Array.hpp"
#include "Array.tpp"

int main(void)
{
    {
        std::cout << "Main 0:\n***Should construct 5 arrays of char, using all canonical ways to do so, and print them. The copies should be deep.\n-----" << std::endl;
        Array<char>  a;
        Array<char>  b(3);
        Array<char>  c(b);
        Array<char>  d(3);
        Array<char>  e = d;

        try
        {
            std::cout << "size of a = " << a.size() << std::endl;
            std::cout << "content of a = " << a << std::endl;

            std::cout << "size of b = " << b.size() << std::endl;
            std::cout << "size of c = " << c.size() << std::endl;
            std::cout << "b, BEFORE : " << b << std::endl;
            std::cout << "c, BEFORE : " << c << std::endl;
            c[0] = 'h';
            c[1] = 'i';
            c[2] = '!';
            std::cout << "c, AFTER : " << c << std::endl;
            std::cout << "b, AFTER : " << b << std::endl;

    
            std::cout << "size of d = " << d.size() << std::endl;
            std::cout << "size of e = " << e.size() << std::endl;
            std::cout << "d, BEFORE : " << d << std::endl;
            std::cout << "e, BEFORE : " << e << std::endl;
            e[0] = 'h';
            e[1] = 'e';
            e[2] = 'y';
            std::cout << "e, AFTER : " << e << std::endl;
            std::cout << "d, AFTER : " << d << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "==============" << std::endl;
    }
    {
        std::cout << "Main 1:\n***Should construct an empty array and print it.\n-----" << std::endl;
        Array<int>  emptyArray;

        try
        {
            std::cout << "size = " << emptyArray.size() << std::endl;
            std::cout << "content = " << emptyArray << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "==============" << std::endl;
    }
    {
        std::cout << "Main 2:\n***Should construct an array of 3 floats. When trying to access an out of bounds element, should throw exception.\n-----" << std::endl;
        Array<float>  arr(3);

        try
        {
            std::cout << "size = " << arr.size() << std::endl;
            std::cout << "content, BEFORE = " << arr << std::endl;

            arr[0] = 1.2;
            arr[1] = 2.3;
            arr[2] = 3.4;
            std::cout << "content, AFTER = " << arr << std::endl;
            arr[3] = 4.5;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "==============" << std::endl;
    }
    return (0);
}
