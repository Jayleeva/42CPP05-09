#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>

# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"


class Intern
{
    public:
        Intern();
        Intern(Intern &original);
        Intern const &operator=(Intern & original);
        ~Intern();

        AForm *makeForm(std::string title, std::string target);
};

typedef AForm *(*constructorPtr)(const std::string);

#endif 