#include "genandid.hpp"

Base *generate(void)
{
    std::srand((unsigned) time(0));
    int lottery = rand() % 3;
    if (lottery == 1)
        return (new A());
    else if (lottery == 2)
        return (new B());
    else
        return (new C());
}

void identify(Base* p)
{
    if (!testAptr(p))
    {
        if (!testBptr(p))
        {
            if (!testCptr(p))
                std::cout << "Type of pointer : none." << std::endl;
            else
                std::cout << "Type of pointer : C" << std::endl;
        }
        else
            std::cout << "Type of pointer : B" << std::endl;
    }
    else
        std::cout << "Type of pointer : A" << std::endl;
}

void identify(Base& p)
{
    if (!testAref(p))
    {
        if (!testBref(p))
        {
            if (!testCref(p))
                std::cout << "Type of reference : none." << std::endl;
            else
                std::cout << "Type of reference : C" << std::endl;
        }
        else
            std::cout << "Type of reference : B" << std::endl;
    }
    else
        std::cout << "Type of reference : A" << std::endl;
}