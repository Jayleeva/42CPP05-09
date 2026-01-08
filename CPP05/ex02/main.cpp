#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n- bureaucrat should be authorized to sign and execute the first three forms\n- should then be decremented\n- while they should still able to sign the remaining ones, they should no longer be able to execute the last.\n****" << std::endl; 
        
        AForm   *sf = new ShrubberyCreationForm("home");
        AForm   *sf1 = new RobotomyRequestForm("files");
        AForm   *sf2 = new PresidentialPardonForm("user");
        try
        {
            ShrubberyCreationForm   sf3("home");
            ShrubberyCreationForm   sf4(sf3);
            ShrubberyCreationForm   sf5 = sf4;

            Bureaucrat              b("Bettany", 42);

            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            std::cout << *sf << std::endl;
            std::cout << *sf1 << std::endl;
            std::cout << *sf2 << std::endl;
            std::cout << sf3 << std::endl;
            std::cout << sf4 << std::endl;
            std::cout << sf5 << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(*sf);
            b.signForm(*sf1);
            b.signForm(*sf2);
            std::cout << "---" << std::endl;

            std::cout << *sf << std::endl;
            std::cout << *sf1 << std::endl;
            std::cout << *sf2 << std::endl;
            std::cout << "---" << std::endl;

            b.executeForm(*sf);
            b.executeForm(*sf1);
            b.executeForm(*sf2);
            std::cout << "---" << std::endl;

            b.decrementGrade(96);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(sf3);
            b.signForm(sf4);
            b.signForm(sf5);
            std::cout << "---" << std::endl;

            std::cout << sf3 << std::endl;
            std::cout << sf4 << std::endl;
            std::cout << sf5 << std::endl;
            std::cout << "---" << std::endl;

            b.executeForm(sf5);
            std::cout << "---" << std::endl;
            delete sf;
            delete sf1;
            delete sf2;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            delete sf;
            delete sf1;
            delete sf2;
        }
        std::cout << "======================" << std::endl;
    }
    return (0);
}