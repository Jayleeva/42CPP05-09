#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include <fstream>
# include "AForm.hpp"

class ShrubberyCreationForm: public AForm
{
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm &original);
		ShrubberyCreationForm const &operator=(ShrubberyCreationForm const &original);
		~ShrubberyCreationForm();

		void execute(Bureaucrat const &executor) const;

	private:
		const std::string	target;
};

#endif