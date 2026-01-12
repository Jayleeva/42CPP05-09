#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(): title("untitled"), grade_to_sign(150), grade_to_execute(150)
{
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: Default constructor called" << DEFAULT << std::endl;
}

AForm::AForm(const std::string title, const int grade_to_sign, const int grade_to_execute): title(title), grade_to_sign(grade_to_sign), grade_to_execute(grade_to_execute)
{
    if (grade_to_sign < 1 || grade_to_execute < 1)
        throw GradeIsTooHighException();
    if (grade_to_sign > 150 || grade_to_execute > 150)
        throw GradeIsTooLowException();
    this->is_signed = false;
    std::cout << YELLOW << "[FORM]: String and int constructor called" << DEFAULT << std::endl;
}

AForm::AForm(const AForm &original): title(original.title), grade_to_sign(original.grade_to_sign), grade_to_execute(original.grade_to_execute)
{
	std::cout << YELLOW << "[FORM]: Copy constructor called" << DEFAULT << std::endl;
    *this = original;
}

AForm const &AForm::operator=(AForm const &original)
{
    if (this != &original)
	{
        this->is_signed = false;
    }
    std::cout << YELLOW << "[FORM]: Assignment operator overload called" << DEFAULT << std::endl;
    return (*this);
}

AForm::~AForm()
{
    std::cout << YELLOW << "[FORM]: Default destructor called" << DEFAULT << std::endl;
}

std::string AForm::getTitle() const
{
    return(this->title);
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

void AForm::checkGradeToExecute(Bureaucrat const &executor) const
{
    if (executor.getGrade() > this->getGradeToExecute())
        throw GradeIsTooLowException();
}

void AForm::checkIsSigned() const
{
    if (!this->getIsSigned())
        throw FormNotSignedException();
}

std::ostream &operator<<(std::ostream &out, AForm const &f)
{
	out << f.getTitle() << "'s information: " << std::endl;
    out << "- is signed = " << f.getIsSigned() << std::endl;
    out << "- grade to sign = " << f.getGradeToSign() << std::endl;
    out << "- grade to execute = " << f.getGradeToExecute() << std::endl;
	return (out);
}
