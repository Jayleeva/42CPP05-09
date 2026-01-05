#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
    std::cout << YELLOW << "[BUREAUCRAT]: Default constructor called" << DEFAULT << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade)
{
    if (grade < 1)
        throw GradeTooLowException();
    else if (grade > 150)
        throw GradeTooHighException();
    this->name = name;
    this->grade = grade;
    std::cout << YELLOW << "[BUREAUCRAT]: String and int constructor called" << DEFAULT << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &original)
{
	std::cout << YELLOW << "[BUREAUCRAT]: Copy constructor called" << DEFAULT << std::endl;
	*this = original;
}

Bureaucrat const &Bureaucrat::operator=(Bureaucrat const &original)
{
    if (this != &original)
	{
        this->name = original.name;
        this->grade = original.grade;
    }
    std::cout << YELLOW << "[BUREAUCRAT]: Copy assignment operator = called" << DEFAULT << std::endl;
    return (*this);
}

Bureaucrat::~Bureaucrat()
{
    std::cout << YELLOW << "[BUREAUCRAT]: Default destructor called" << DEFAULT << std::endl;
}

int Bureaucrat::operator-=(int n) const
{
    if (this->grade - n < 1)
        throw GradeTooHighException();
    return (this->grade - n);
}

int Bureaucrat::operator+=(int n) const
{
    if (this->grade + n > 150)
        throw GradeTooLowException();
    return (this->grade + n);
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
    this->grade -= n;
    std::cout << this->name << " 's grade incremented by " << n << std::endl;
}

void Bureaucrat::decrementGrade(int n)
{
    this->grade += n;
    std::cout << this->name << " 's grade decremented by " << n << std::endl;
}


