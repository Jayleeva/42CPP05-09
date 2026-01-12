#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): name("unknown")
{
    this->grade = 150;
    std::cout << YELLOW << "[BUREAUCRAT]: Default constructor called" << DEFAULT << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade): name(name)
{
    if (grade < 1)
        throw GradeTooHighException();
    else if (grade > 150)
        throw GradeTooLowException();
    this->grade = grade;
    std::cout << YELLOW << "[BUREAUCRAT]: String and int constructor called" << DEFAULT << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &original): name(original.name)
{
	std::cout << YELLOW << "[BUREAUCRAT]: Copy constructor called" << DEFAULT << std::endl;
	*this = original;
}

Bureaucrat const &Bureaucrat::operator=(Bureaucrat const &original)
{
    if (this != &original)
	{
        this->grade = original.grade;
    }
    std::cout << YELLOW << "[BUREAUCRAT]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

Bureaucrat::~Bureaucrat()
{
    std::cout << YELLOW << "[BUREAUCRAT]: Default destructor called" << DEFAULT << std::endl;
}

const std::string Bureaucrat::getName() const
{
    return(this->name);
}

int Bureaucrat::getGrade() const
{
    return(this->grade);
}

void Bureaucrat::incrementGrade(int n)
{
    if (this->grade - n < 1)
        throw GradeTooHighException();
    this->grade -= n;
    std::cout << this->name << "'s grade incremented by " << n << std::endl;
}

void Bureaucrat::decrementGrade(int n)
{
    if (this->grade + n > 150)
        throw GradeTooLowException();
    this->grade += n;
    std::cout << this->name << "'s grade decremented by " << n << std::endl;
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &b)
{
	out << b.getName() << ", grade " << b.getGrade();
	return (out);
}