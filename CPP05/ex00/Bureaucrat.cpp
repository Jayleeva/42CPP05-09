#include "Bureaucrat.hpp"

//pas de reassignation du nom dans la surcharge de l'operateur d'assignation parce que 
// - comme nom est une constante, besoin de const_cast pour lui (re)donner une valeur.
// - or, const_cast ne fonctionne qu'avec des pointeurs ou des references,
// -  une reference ne peut pas ne pas etre initialisee,
// -   on ne peut pas utiliser : name(original.name) dans une surcharge
// -   (pour nom par defaut) initialiser avec : name("unknown") ne fonctionne pas avec une reference, uniquement avec un pointeur ou un element non pointe,
// -    utiliser un pointeur fait que tous les bureaucrates ont le meme nom somehow.
// marche sans anyhow. Pas compris comment mais soit.

Bureaucrat::Bureaucrat() : name("unknown")
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