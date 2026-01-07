#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
    {
        std::cout << "Main 0:\n- bureaucrat should be authorized to sign and execute the first two forms\n- should then be decremented\n- while they should still able to sign the two last ones, they should no longer be able to execute the last.\n****" << std::endl; 
        try
        {
            Bureaucrat                  b("Bettany", 42);
            ShrubberyCreationForm       sf("home");
            ShrubberyCreationForm       sf1("files");
            ShrubberyCreationForm       sf2(sf);
            ShrubberyCreationForm       sf3 = sf1;

            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(sf);
            //b.executeForm(sf);
            b.signForm(sf1);
            //b.executeForm(sf1);
            std::cout << "---" << std::endl;

            b.decrementGrade(96);
            std::cout << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(sf2);
            //b.executeForm(sf2);
            b.signForm(sf3);
            //b.executeForm(sf3);
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