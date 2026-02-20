#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <ctime>
# include <algorithm>
# include <cmath>
# include <vector>
# include <deque>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"

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

		void	splitBigSmall(std::vector<unsigned int>&current);
		void	binaryInsertSmall(unsigned int ui);
		void	mergePairs(size_t size, std::vector<unsigned int>&current);
		void	standardBinaryInsert(unsigned int ui);
		void	binaryInsertBig();

		void	sortContainer();
		void	printContainer();

	private:
		std::vector<unsigned int>	container;
		std::vector<unsigned int>	small;
		std::vector<unsigned int>	big;
		std::vector<unsigned int>	leftover;
};

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal);

#endif
