#include "Intern.hpp"

Intern::Intern()
{
    std::cout << YELLOW << "[INTERN]: Default constructor called" << DEFAULT << std::endl;
}

Intern::Intern(const Intern &original)
{
	std::cout << YELLOW << "[INTERN]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

Intern const &Intern::operator=(Intern const &original)
{
    (void)original;
    std::cout << YELLOW << "[INTERN]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

Intern::~Intern()
{
    std::cout << YELLOW << "[INTERN]: Default destructor called" << DEFAULT << std::endl;
}

static AForm	*newShrubbery(const std::string target)
{
	return (new ShrubberyCreationForm(target));
}

static AForm	*newRobotomy(const std::string target)
{
	return (new RobotomyRequestForm(target));
}

static AForm	*newPresidential(const std::string target)
{
	return (new PresidentialPardonForm(target));
}

static int	ft_to_index(std::string f)
{
    std::string const forms[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	int i = 0;
	while (i < 3)
	{
		if (f == forms[i])
			return (i) ;
		i ++;
	}
	return (-1);
}

AForm *Intern::makeForm(std::string title, std::string target) const
{
    AForm *form = NULL;
    constructorPtr	FormConstruct[3] = {&newShrubbery, &newRobotomy, &newPresidential};
    
    int i = ft_to_index(title);
    if (i == -1)
        std::cout << "Error: form does not exist." << std::endl;
    else
    {
        form = FormConstruct[i](target);
        std::cout << "Intern creates " << form->getName() << std::endl;
    }
    //std::cout << YELLOW << "[INTERN]: makeForm function called" << DEFAULT << std::endl;
    return (form);
}