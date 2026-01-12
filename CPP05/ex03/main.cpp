#include "Intern.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

void    delete_forms(AForm **f)
{
    delete f[0];
    delete f[1];
    delete f[2];
    delete f[3];
}

int main(void)
{
    {
        std::cout << "Main 0:\n- intern should make one of every form\n- should not be able to make the fake one\n- bureaucrat should be authorized to sign and execute the existing ones.\n****"<< std::endl;

        Intern  drone;
        AForm   *f[4];
        try
        {
            f[0] = drone.makeForm("shrubbery creation", "home");
            f[1] = drone.makeForm("robotomy request", "files");
            f[2] = drone.makeForm("presidential pardon", "user");
            f[3] = drone.makeForm("form anihilation", "forms");

            Bureaucrat  b("Brooke", 1);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(*f[0]);
            b.signForm(*f[1]);
            b.signForm(*f[2]);
            std::cout << "---" << std::endl;

            b.executeForm(*f[0]);
            b.executeForm(*f[1]);
            b.executeForm(*f[2]);
            std::cout << "---" << std::endl;
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            delete_forms(f);
        }
        delete_forms(f);
        std::cout << "======================" << std::endl;
    }
    return (0);
}