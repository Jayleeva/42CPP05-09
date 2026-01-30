#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <ctime>
# include <algorithm>
# include <cmath>
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

		typedef typename std::vector<int>::iterator iterator;

		std::vector<unsigned int>	getContainer() const;
		void						setContainer(std::vector<int>::iterator begin, std::vector<int>::iterator end);

		//void	merge_small(std::vector<unsigned int> container, size_t first, size_t last);
		//void	merge_big(std::vector<unsigned int> container, size_t first, size_t last);
		//void	insert_big_in_small();

		void	formPairs();
		void	mergePairs();
		void	insertBigInSmall();
		void	insertLeftover();

		void	sortContainer(size_t size);
		void	printContainer();

	private:
		std::vector<unsigned int>	container;
		std::vector<unsigned int>	small;
		std::vector<unsigned int>	big;
		std::vector<unsigned int>	leftover;
};

#endif
