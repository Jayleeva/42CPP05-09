#include "genandid.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base    *testAptr(Base *p)
{
    A *test = dynamic_cast<A*>(p);
    return (test);
}

Base    *testBptr(Base *p)
{
    B *test = dynamic_cast<B*>(p);
    return (test);
}

Base    *testCptr(Base *p)
{
    C *test = dynamic_cast<C*>(p);
    return (test);
}



int testAref(Base &p)
{
    try
    {
        A &test = dynamic_cast<A&>(p);
        (void)test;
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}

int testBref(Base &p)
{
    try
    {
        B &test = dynamic_cast<B&>(p);
        (void)test;
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}

int testCref(Base &p)
{
    try
    {
        C &test = dynamic_cast<C&>(p);
        (void)test;
        return (1);
    }
    catch (std::exception &e)
    {
        return (0);
    }
}