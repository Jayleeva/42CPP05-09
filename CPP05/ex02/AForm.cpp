#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): grade_to_sign(150), grade_to_execute(150)
{
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: Default constructor called" << DEFAULT << std::endl;
}

AForm::AForm(const std::string name, const int grade_to_sign, const int grade_to_execute): name(&name), grade_to_sign(grade_to_sign), grade_to_execute(grade_to_execute)
{
    if (grade_to_sign < 1 || grade_to_execute < 1)
        throw GradeIsTooHighException();
    if (grade_to_sign > 150 || grade_to_execute > 150)
        throw GradeIsTooLowException();
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: String and int constructor called" << DEFAULT << std::endl;
}

AForm::AForm(const AForm &original): name(original.name), grade_to_sign(original.grade_to_sign), grade_to_execute(original.grade_to_execute)
{
	std::cout << YELLOW << "[FORM]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

AForm const &AForm::operator=(AForm const &original)
{
    if (this != &original)
	{
        *const_cast<std::string*>(this->name) = *(original.name);
        this->is_signed = false;
    }
    std::cout << YELLOW << "[FORM]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

AForm::~AForm()
{
    std::cout << YELLOW << "[FORM]: Default destructor called" << DEFAULT << std::endl;
}

std::string AForm::getName() const
{
    return(*(this->name));
}

bool AForm::getIsSigned() const
{
    return(this->is_signed);
}

int AForm::getGradeToSign() const
{
    return(this->grade_to_sign);
}

int AForm::getGradeToExecute() const
{
    return(this->grade_to_execute);
}

void AForm::beSigned(Bureaucrat const *b)
{
    if (b->getGrade() > this->grade_to_sign)
        throw GradeIsTooLowException();
    this->is_signed = true;
}

void AForm::execute(Bureaucrat const &executor) const
{
    (void)executor;
    std::cout << YELLOW << "[FORM]: execute function called" << DEFAULT << std::endl;
}

std::ostream &operator<<(std::ostream &out, AForm const &f)
{
	out << f.getName();
    out << ", is signed = " << f.getIsSigned();
    out << ", grade to sign = " << f.getGradeToSign();
    out << ", grade to execute = " << f.getGradeToExecute();
	return (out);
}