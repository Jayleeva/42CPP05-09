#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n- bureaucrat should be authorized to sign and execute the form.\n****"<< std::endl;

        AForm   *f = new ShrubberyCreationForm("home");
        try
        {
            Bureaucrat  b("Billie", 137);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            std::cout << *f << std::endl;

            b.signForm(*f);
            std::cout << "---" << std::endl;

            std::cout << *f << std::endl;
            std::cout << "---" << std::endl;

            b.executeForm(*f);
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            delete f;
        }
        delete f;
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 1:\n- bureaucrat should be authorized to sign the form, but not execute it because of their grade.\n****"<< std::endl;

        AForm   *f1 = new RobotomyRequestForm("files");
        try
        {
            Bureaucrat  b("Bridget", 48);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(*f1);
            std::cout << "---" << std::endl;

            b.executeForm(*f1);
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            delete f1;
        }
        delete f1;
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 2:\n- bureaucrat should not be authorized to execute the form because they didn't sign it.\n- then should sign it and execute it.\n****"<< std::endl;

        AForm   *f2 = new PresidentialPardonForm("user");
        try
        {
            Bureaucrat  b("Bob", 4);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.executeForm(*f2);
            std::cout << "---" << std::endl;

            b.signForm(*f2);
            std::cout << "---" << std::endl;

            b.executeForm(*f2);
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            delete f2;
        }
        delete f2;
        std::cout << "======================" << std::endl;
    }
    {
        std::cout << "Main 3:\n- bureaucrat should not be authorized to sign the forms because of their grade\n- should then be incremented\n- they should not be authorized to execute them because they're not signed.\n****" << std::endl; 
        
        try
        {
            ShrubberyCreationForm   f3("home");
            ShrubberyCreationForm   f4(f3);
            ShrubberyCreationForm   f5 = f4;

            Bureaucrat              b("Bettany", 148);

            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(f3);
            b.signForm(f4);
            b.signForm(f5);
            std::cout << "---" << std::endl;

            b.incrementGrade(40);
            b.executeForm(f3);
            b.executeForm(f4);
            b.executeForm(f5);
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