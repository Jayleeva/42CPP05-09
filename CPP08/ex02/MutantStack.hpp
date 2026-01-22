#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <algorithm>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class MutantStack
{
	public:
		MutantStack();
		MutantStack(MutantStack const &original);
		MutantStack &operator=(MutantStack const &original);
		~MutantStack();

	private:

};

#endif