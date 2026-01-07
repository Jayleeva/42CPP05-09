#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137)
{
    std::cout << YELLOW << "[SHRUBBERRY]: Default constructor called" << DEFAULT << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137)
{
	std::cout << target << std::endl;
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
        *const_cast<std::string*>(this->name) = *(original.name);
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
	(void)executor;
    std::cout << YELLOW << "[SHRUBBERRY]: execute function called" << DEFAULT << std::endl;
}