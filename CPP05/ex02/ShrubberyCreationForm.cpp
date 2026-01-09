#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), target("unknown")
{
    std::cout << YELLOW << "[SHRUBBERRY]: Default constructor called" << DEFAULT << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), target(target)
{
    std::cout << YELLOW << "[SHRUBBERRY]: String and int constructor called" << DEFAULT << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &original) : AForm("ShrubberyCreationForm", 145, 137)
{
	std::cout << YELLOW << "[SHRUBBERRY]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

ShrubberyCreationForm const &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &original)
{
    if (this != &original)
	{
        this->is_signed = false;
    }
    std::cout << YELLOW << "[SHRUBBERRY]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}	

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << YELLOW << "[SHRUBBERRY]: Default destructor called" << DEFAULT << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	std::ofstream	outfile;

    this->AForm::checkGradeToExecute(executor);
	outfile.open((this->target + "_shrubbery").c_str());
	if (outfile.good() == false)
        throw OpenFileFailedException();
    outfile << "                     .o00o" << std::endl;
    outfile << "                   o000000oo" << std::endl;
    outfile << "                  00000000000o" << std::endl;
    outfile << "                 00000000000000" << std::endl;
    outfile << "              oooooo  00000000  o88o" << std::endl;
    outfile << "           ooOOOOOOOoo  ```''  888888" << std::endl;
    outfile << "         OOOOOOOOOOOO'.qQQQQq. `8888'" << std::endl;
    outfile << "        oOOOOOOOOOO'.QQQQQQQQQQ/.88'" << std::endl;
    outfile << "        OOOOOOOOOO'.QQQQQQQQQQ/ /q" << std::endl;
    outfile << "         OOOOOOOOO QQQQQQQQQQ/ /QQ" << std::endl;
    outfile << "           OOOOOOOOO `QQQQQQ/ /QQ'" << std::endl;
    outfile << "             OO:F_P:O `QQQ/  /Q'" << std::endl;
    outfile << "                \\. \\ |  // |" << std::endl;
    outfile << "                d\\ \\\\|_////" << std::endl;
    outfile << "                qP| \\ _' `|Ob" << std::endl;
    outfile << "                   \\  / \\  \\Op" << std::endl;
    outfile << "                   |  | O| |" << std::endl;
    outfile << "           _       /\\. \\_/ /\\" << std::endl;
    outfile << "            `---__/|_\\   //|  __" << std::endl;
    outfile << "                  `-'  `-'`-'-'" << std::endl;
    outfile.close();
    std::cout << YELLOW << "[SHRUBBERRY]: execute function called" << DEFAULT << std::endl;
}