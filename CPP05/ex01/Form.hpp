#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class Bureaucrat;

class Form
{
    public:
        Form();
        Form(const std::string name, const int grade_to_sign, const int grade_to_execute);
        Form(const Form &original);
        Form const &operator=(Form const &original);
        ~Form();

        std::string getName() const;
        bool getIsSigned() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;

        void beSigned(Bureaucrat const *b);

    private:
        const std::string   *name;
        bool                is_signed;
        const int           grade_to_sign;
        const int           grade_to_execute;

        class GradeIsTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Exception: Grade is too high.");
                }
        };
        class GradeIsTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Exception: Grade is too low.");
                }
        };
};

std::ostream &operator<<(std::ostream &out, Form const &f);

#endif