#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class Bureaucrat;

class AForm
{
    public:
        AForm const &operator=(AForm const &original);
        virtual ~AForm();

        virtual std::string getName() const;
        bool getIsSigned() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;

        void beSigned(Bureaucrat const *b);
        virtual void execute(Bureaucrat const &executor) const = 0;
        void checkGradeToExecute(Bureaucrat const &executor) const;
        void checkIsSigned() const;

    protected:
        AForm();
        AForm(const std::string name, const int grade_to_sign, const int grade_to_execute);
        AForm(const AForm &original);
        const std::string   &name;
        bool                is_signed;
        const int           &grade_to_sign;
        const int           &grade_to_execute;

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
        class FormNotSignedException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Exception: Form is not signed.");
                }
        };
};

std::ostream &operator<<(std::ostream &out, AForm const &f);

#endif