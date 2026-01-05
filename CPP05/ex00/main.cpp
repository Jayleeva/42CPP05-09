#include "Bureaucrat.hpp"

int main(void)
{
    {
        std::cout << "Main 0: everything should be fine\n****" << std::endl; 
        try
        {
            Bureaucrat  a = Bureaucrat("Bettany", 43);
            Bureaucrat  b = Bureaucrat("Bob", 108);
            Bureaucrat  e = Bureaucrat(a);
            Bureaucrat  f = b;

            std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << e.getName() << ", bureaucrat grade " << e.getGrade() << std::endl;
            std::cout << f.getName() << ", bureaucrat grade " << f.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            a.incrementGrade(42);
            b.decrementGrade(42);
            e.incrementGrade(1);
            f.decrementGrade(1);
            std::cout << "---" << std::endl;

            std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << e.getName() << ", bureaucrat grade " << e.getGrade() << std::endl;
            std::cout << f.getName() << ", bureaucrat grade " << f.getGrade() << std::endl;
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
            Bureaucrat  c = Bureaucrat("Bridget", 0);
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
            Bureaucrat  d = Bureaucrat("Ben", 151);
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
            Bureaucrat  a = Bureaucrat("Bettany", 42);

            std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            a.incrementGrade(42);

            std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
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
            Bureaucrat  b = Bureaucrat("Bob", 109);

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