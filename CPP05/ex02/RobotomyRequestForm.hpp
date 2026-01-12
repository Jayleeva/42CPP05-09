#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <ostream>
# include <ctime>
# include <cstdlib>
# include "AForm.hpp"


class RobotomyRequestForm: public AForm
{
	public:
		RobotomyRequestForm();
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm &original);
		RobotomyRequestForm const &operator=(RobotomyRequestForm const &original);
		~RobotomyRequestForm();

		void execute(Bureaucrat const &executor) const;

	private:
		const std::string	target;
};

#endif