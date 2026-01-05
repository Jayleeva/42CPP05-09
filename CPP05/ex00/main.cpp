#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat  a = Bureaucrat("Bettany", 43);
        Bureaucrat  b = Bureaucrat("Bob", 108);
        Bureaucrat  c = Bureaucrat("Bridget", 0);
        Bureaucrat  d = Bureaucrat("Ben", 151);
        Bureaucrat  e = Bureaucrat(a);
        Bureaucrat  f = b;

        std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
        std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
        //std::cout << c.getName() << ", bureaucrat grade " << c.getGrade() << std::endl;
        //std::cout << d.getName() << ", bureaucrat grade " << d.getGrade() << std::endl;
        std::cout << e.getName() << ", bureaucrat grade " << e.getGrade() << std::endl;
        std::cout << f.getName() << ", bureaucrat grade " << f.getGrade() << std::endl;

        a.incrementGrade(42);
        b.decrementGrade(42);
        e.incrementGrade(1);
        f.decrementGrade(1);

        std::cout << a.getName() << ", bureaucrat grade " << a.getGrade() << std::endl;
        std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
        //std::cout << c.getName() << ", bureaucrat grade " << c.getGrade() << std::endl;
        //std::cout << d.getName() << ", bureaucrat grade " << d.getGrade() << std::endl;
        //std::cout << e.getName() << ", bureaucrat grade " << e.getGrade() << std::endl;
        //std::cout << f.getName() << ", bureaucrat grade " << f.getGrade() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}