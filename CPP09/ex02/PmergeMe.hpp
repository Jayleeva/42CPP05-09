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


typedef struct s_dataVec
{
	std::vector<unsigned int>	container;
	std::vector<unsigned int>	small;
	std::vector<unsigned int>	big;
}								t_dataVec;

typedef struct s_dataDeq
{
	std::deque<unsigned int>	dataDeq;
	std::deque<unsigned int>	small;
	std::deque<unsigned int>	big;
}								t_dataDeq;

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		//typedef typename T::iterator iterator;

		std::vector<unsigned int>	getVector() const;
		void						setVector(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end);

		std::deque<unsigned int>	getDeque() const;
		void						setDeque(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end);
	
		template<typename T>
		void	splitBigSmall(T &current);
		void	binaryInsertSmall(unsigned int ui);
		template<typename T>
		void	mergePairs(size_t size, T &current);
		void	standardBinaryInsert(unsigned int ui);
		void	binaryInsertBig();

		void	sortContainer();
		void	printContainer();

	private:
		t_dataVec	dataVec;
		t_dataDeq	dataDeq;
};

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal);

#endif
