#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 145, 137), target("unknown")
{
    std::cout << YELLOW << "[ROBOTOMY]: Default constructor called" << DEFAULT << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 145, 137), target(target)
{
    std::cout << YELLOW << "[ROBOTOMY]: String and int constructor called" << DEFAULT << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &original) : AForm("RobotomyRequestForm", 145, 137)
{
	std::cout << YELLOW << "[ROBOTOMY]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

RobotomyRequestForm const &RobotomyRequestForm::operator=(RobotomyRequestForm const &original)
{
    if (this != &original)
	{
        this->is_signed = false;
    }
    std::cout << YELLOW << "[ROBOTOMY]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}	

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << YELLOW << "[ROBOTOMY]: Default destructor called" << DEFAULT << std::endl;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    this->AForm::checkGradeToExecute(executor);
    std::cout << YELLOW << "[ROBOTOMY]: execute function called" << DEFAULT << std::endl;
}