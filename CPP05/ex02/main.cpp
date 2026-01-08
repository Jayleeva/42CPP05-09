#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

void    deleteForms(AForm **array, int n)
{
    int i;

    for (i = 0; i < n; i ++)
    {
        if (array[i])
            delete array[i];
    }
}

int main(void)
{
    {
        int     n = 2;
        AForm   *array[n];
        std::cout << "Main 0:\n- bureaucrat should be authorized to sign and execute the first two forms\n- should then be decremented\n- while they should still able to sign the two last ones, they should no longer be able to execute the last.\n****" << std::endl; 
        try
        {
            Bureaucrat                  b("Bettany", 42);
           
            AForm                       *sf = new ShrubberyCreationForm("home");
            //ShrubberyCreationForm       sf("home");
            AForm                       *sf1 = new ShrubberyCreationForm("files");
            //ShrubberyCreationForm       sf2 = new ShrubberyCreationForm(*sf);
            //ShrubberyCreationForm       sf3 = new ShrubberyCreationForm;
            //*sf3 = *sf1;

            array[0] = sf;
            array[1] = sf1;
            std::cout << b << std::endl;
            //std::cout << sf << std::endl;
            //std::cout << sf1 << std::endl;
            //std::cout << sf2 << std::endl;
            //std::cout << sf3 << std::endl;
            std::cout << "---" << std::endl;

            b.signForm(*sf);
            b.executeForm(*sf);
            b.signForm(*sf1);
            b.executeForm(*sf1);
            std::cout << "---" << std::endl;

            b.decrementGrade(96);
            std::cout << b << std::endl;
            std::cout << "---" << std::endl;

            /*b.signForm(sf2);
            b.executeForm(sf2);
            b.signForm(sf3);
            b.executeForm(sf3);*/
            std::cout << "---" << std::endl;
            deleteForms(array, n);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
            deleteForms(array, n);
        }
        std::cout << "======================" << std::endl;
    }
    return (0);
}