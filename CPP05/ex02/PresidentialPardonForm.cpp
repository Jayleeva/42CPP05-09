#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 145, 137), target("unknown")
{
    std::cout << YELLOW << "[PRESIDENTIAL]: Default constructor called" << DEFAULT << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 145, 137), target(target)
{
    std::cout << YELLOW << "[PRESIDENTIAL]: String and int constructor called" << DEFAULT << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &original) : AForm("PresidentialPardonForm", 145, 137)
{
	std::cout << YELLOW << "[PRESIDENTIAL]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

PresidentialPardonForm const &PresidentialPardonForm::operator=(PresidentialPardonForm const &original)
{
    if (this != &original)
	{
        this->is_signed = false;
    }
    std::cout << YELLOW << "[PRESIDENTIAL]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}	

PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << YELLOW << "[PRESIDENTIAL]: Default destructor called" << DEFAULT << std::endl;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    this->AForm::checkGradeToExecute(executor);
    std::cout << YELLOW << "[PRESIDENTIAL]: execute function called" << DEFAULT << std::endl;
}