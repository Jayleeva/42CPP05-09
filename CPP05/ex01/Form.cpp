#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(): name("untitled"), grade_to_sign(150), grade_to_execute(150)
{
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: Default constructor called" << DEFAULT << std::endl;
}

Form::Form(const std::string name, const int grade_to_sign, const int grade_to_execute): name(name), grade_to_sign(grade_to_sign), grade_to_execute(grade_to_execute)
{
    if (grade_to_sign < 1 || grade_to_execute < 1)
        throw GradeIsTooHighException();
    if (grade_to_sign > 150 || grade_to_execute > 150)
        throw GradeIsTooLowException();
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: String and int constructor called" << DEFAULT << std::endl;
}

Form::Form(const Form &original): name(original.name), grade_to_sign(original.grade_to_sign), grade_to_execute(original.grade_to_execute)
{
    *this = original;
    this->is_signed = false;
	std::cout << YELLOW << "[FORM]: Copy constructor called" << DEFAULT << std::endl;
}

Form const &Form::operator=(Form const &original)
{
    if (this != &original)
	{
        //this->name = original.name;
        //this->grade_to_sign = original.grade_to_sign;
        //this->grade_to_execute = original.grade_to_execute;
        this->is_signed = false;
    }
    std::cout << YELLOW << "[FORM]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

Form::~Form()
{
    std::cout << YELLOW << "[FORM]: Default destructor called" << DEFAULT << std::endl;
}

std::string Form::getName() const
{
    return(this->name);
}

bool Form::getIsSigned() const
{
    return(this->is_signed);
}

int Form::getGradeToSign() const
{
    return(this->grade_to_sign);
}

int Form::getGradeToExecute() const
{
    return(this->grade_to_execute);
}

void Form::beSigned(Bureaucrat const *b)
{
    if (b->getGrade() > this->grade_to_sign)
        throw GradeIsTooLowException();
    this->is_signed = true;
}