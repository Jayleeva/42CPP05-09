#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n- all forms should be valid\n- bureaucrat should be authorized to sign the first two\n- should then be decremented\n- while they should still able to sign the third one, they should no longer be able to sign the last one.\n****" << std::endl; 
        try
        {
            Bureaucrat  b("Bettany", 42);
            Form        f("Say hi", 84, 42);
            Form        f1("Say bye", 60, 42);
            Form        f2(f);
            Form        f3 = f1;

            std::cout << b << std::endl;
            std::cout << f << std::endl;
            std::cout << f1 << std::endl;
            std::cout << f2 << std::endl;
            std::cout << f3 << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(f);
            b.signForm(f1);
            std::cout << "---" << std::endl;

            b.decrementGrade(42);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(f2);
            b.signForm(f3);
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 1: form sign grade should be too high at construction\n****" << std::endl; 
        try
        {
            Form  f("Say hi", 0, 150);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 2: form sign grade should be too low at construction\n****" << std::endl; 
        try
        {
            Form  f("Say hi", 151, 1);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 3: form execute grade should be too high at construction\n****" << std::endl; 
        try
        {
            Form  f("Say bye", 0, 150);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 4: form execute grade should be too low at construction\n****" << std::endl; 
        try
        {
            Form  f("Say bye", 151, 1);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "======================" << std::endl;
    }
    return (0);
}