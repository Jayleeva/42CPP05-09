#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <ctime>
# include <algorithm>
# include <cmath>
# include <limits>
# include <vector>
# include <deque>

# define MAX_INT std::numeric_limits<int>::max() 

# define VERBIOSE false
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

typedef struct s_dataVec
{
	std::vector<unsigned int>	main;
	std::vector<unsigned int>	pending;
	std::vector<unsigned int>	remaining;
}								t_dataVec;

typedef struct s_dataDeq
{
	std::deque<unsigned int>	main;
	std::deque<unsigned int>	pending;
	std::deque<unsigned int>	remaining;
}								t_dataDeq;

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		std::vector<unsigned int>	getVec() const;
		void						setVec(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end);

		std::deque<unsigned int>	getDeq() const;
		void						setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end);

		ssize_t						sortVector();
		ssize_t						sortDequeue();

	private:
		std::vector<unsigned int>	vec;
		std::deque<unsigned int>	deq;
};

std::vector<unsigned int>::iterator getIte(std::vector<unsigned int> &current, ssize_t pairSize);
std::deque<unsigned int>::iterator getIte(std::deque<unsigned int> &current, ssize_t pairSize);

void	updateIndexes(std::vector<ssize_t> &indexes, ssize_t i, ssize_t blockSize, bool nomatch);
void	updateIndexes(std::deque<ssize_t> &indexes, ssize_t i, ssize_t blockSize, bool nomatch);

void	binaryInsert(std::vector<unsigned int> &container, std::vector<unsigned int>::iterator head, ssize_t blockSize, std::vector<unsigned int>::iterator min_, std::vector<unsigned int>::iterator max_, int type, std::vector<ssize_t> &indexes, bool nomatch);
void	binaryInsert(std::deque<unsigned int> &container, std::deque<unsigned int>::iterator head, ssize_t blockSize, std::deque<unsigned int>::iterator min_, std::deque<unsigned int>::iterator max_, int type, std::deque<ssize_t> &indexes, bool nomatch);

std::vector<unsigned int>	normalMerge(t_dataVec *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::vector<ssize_t> &indexes, std::vector<bool> used, bool nomatch);
std::deque<unsigned int>	normalMerge(t_dataDeq *data, ssize_t blockSize, ssize_t n, ssize_t remaining, std::deque<ssize_t> &indexes, std::deque<bool> used, bool nomatch);

void	updateJacobsthal(std::vector<size_t> &jacobsthal);
void	updateJacobsthal(std::deque<size_t> &jacobsthal);

std::vector<unsigned int>	jacobsthalMerge(t_dataVec *data, ssize_t blockSize, std::vector<ssize_t> &indexes, bool nomatch);
std::deque<unsigned int>	jacobsthalMerge(t_dataDeq *data, ssize_t blockSize, std::deque<ssize_t> &indexes, bool nomatch);

bool	hasNomatch(std::vector<ssize_t>	indexes);
bool	hasNomatch(std::deque<ssize_t>	indexes);

std::vector<ssize_t>	formMainAndPending(t_dataVec *data, ssize_t blockSize, std::vector<unsigned int> &current, std::vector<unsigned int>::iterator ite);
std::deque<ssize_t>		formMainAndPending(t_dataDeq *data, ssize_t blockSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator ite);

void	merging(ssize_t pairSize, std::vector<unsigned int> &current);
void	merging(ssize_t pairSize, std::deque<unsigned int> &current);

void	swapElements(ssize_t blockSize, std::vector<unsigned int>::iterator it, std::vector<unsigned int>::iterator ite);
void	swapElements(ssize_t blockSize, std::deque<unsigned int>::iterator it, std::deque<unsigned int>::iterator ite);

void	sortPairs(ssize_t pairSize, std::vector<unsigned int> &current, std::vector<unsigned int>::iterator max_);
void	sortPairs(ssize_t pairSize, std::deque<unsigned int> &current, std::deque<unsigned int>::iterator max_);

void	swapping(size_t size, std::vector<unsigned int> &current);
void	swapping(size_t size, std::deque<unsigned int> &current);

template<typename T>
void	printContainer(T &container, size_t n)
{
	size_t	max_ = 20;
	size_t	size = container.size();

	for (size_t i = 0; i < size -1 ; i++)
	{
		if (i == max_)
		{
			std:: cout << "[...]" << std::endl;
			return ;
		}
		std::cout << container[i];
		if (n && (i + 1) % n == 0)
			std::cout << " ; ";
		else
			std::cout << ' ';
	}
	std::cout << container[size -1] << std::endl;
};

#endif