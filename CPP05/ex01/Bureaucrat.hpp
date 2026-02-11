#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class Form;

class Bureaucrat
{
    public:
        Bureaucrat();
        Bureaucrat(const std::string name, int grade);
		Bureaucrat(const Bureaucrat &original);
        Bureaucrat const &operator=(Bureaucrat const &original);
        ~Bureaucrat();

        const std::string getName() const;
        int getGrade() const;

        void incrementGrade(int n);
        void decrementGrade(int n);
        void signForm(Form &f);

    private:
        const std::string       &name;
        int                     grade;

        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Exception : Grade is too high.");
                }
        };

        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Exception : Grade is too low.");
                }
        };
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &b);

#endif