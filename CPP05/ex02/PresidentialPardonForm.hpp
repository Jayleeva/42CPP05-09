#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include <fstream>
# include "AForm.hpp"

class PresidentialPardonForm: public AForm
{
	public:
		PresidentialPardonForm();
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm &original);
		PresidentialPardonForm const &operator=(PresidentialPardonForm const &original);
		~PresidentialPardonForm();

		void execute(Bureaucrat const &executor) const;

	private:
		const std::string	target;
};

#endif