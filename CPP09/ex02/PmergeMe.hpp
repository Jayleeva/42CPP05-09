#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		std::vector<unsigned int>	getContainer() const;
		void	setContainer();

		void	sortContainer();

	private:
		std::vector<unsigned int>	vec;
};

std::ostream &operator<<(std::ostream &out, PmergeMe const &p);

#endif