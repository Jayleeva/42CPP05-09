#include "Bureaucrat.hpp"

int main(void)
{
    {
        std::cout << "Main 0: everything should be fine\n****" << std::endl; 
        try
        {
            Bureaucrat  a("Bettany", 43);
            Bureaucrat  b("Bob", 108);
            Bureaucrat  c(a);
            Bureaucrat  d = b;

            std::cout << a << std::endl;
            std::cout << b << std::endl;
            std::cout << c << std::endl;
            std::cout << d << std::endl;
            std::cout << "---" << std::endl;

            a.incrementGrade(42);
            b.decrementGrade(42);
            c.incrementGrade(1);
            d.decrementGrade(1);
            std::cout << "---" << std::endl;

            std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << c.getName() << ", bureaucrat grade " << c.getGrade() << std::endl;
            std::cout << d.getName() << ", bureaucrat grade " << d.getGrade() << std::endl;
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 1: grade should be too high at construction\n****" << std::endl; 
        try
        {
            Bureaucrat  b("Bridget", 0);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 2: grade should be too low at construction\n****" << std::endl; 
        try
        {
            Bureaucrat  b("Ben", 151);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 3: grade should be too high after incrementation\n****" << std::endl; 
        try
        {
            Bureaucrat  b("Bettany", 42);

            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            b.incrementGrade(42);

            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 4: grade should be too low after decrementation\n****" << std::endl; 
        try
        {
            Bureaucrat  b("Bob", 109);

            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            b.decrementGrade(42);

            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    return (0);
}