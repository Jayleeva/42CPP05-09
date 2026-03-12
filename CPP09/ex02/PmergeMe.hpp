#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <ctime>
# include <algorithm>
# include <cmath>
# include <vector>
# include <deque>
# include <limits>

# define MAX_INT std::numeric_limits<int>::max() 

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
	std::vector<size_t> 		jacobsthal;
}								t_dataVec;

typedef struct s_dataDeq
{
	std::deque<unsigned int>						main;
	std::deque<unsigned int>						pending;
	std::deque<unsigned int>						remaining;
	std::deque<size_t> 								jacobsthal;
	std::deque<std::deque<unsigned int>::iterator>	labels;
}								t_dataDeq;

class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		std::deque<unsigned int>	getDeq() const;
		void						setDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end);

		void						sortDequeue();

	private:
		//std::vector<unsigned int>	vec;
		std::deque<unsigned int>	deq;
};

void	binaryInsert(std::vector<unsigned int> &container, unsigned int ui);
void	binaryInsert(std::deque<unsigned int> &container, unsigned int ui);

void	jacobsthalInsert(t_dataVec *data);
void	jacobsthalInsert(t_dataDeq *data);

void	swapping(size_t size, std::vector<unsigned int> &current);
void	swapping(size_t size, std::deque<unsigned int> &current);

void	merging(size_t size, std::vector<unsigned int> &container, std::vector<size_t> &jacobsthal);
void	merging(size_t size, std::deque<unsigned int> &container, std::deque<size_t> &jacobsthal);

void	update_jacobsthal(std::deque<size_t> &jacobsthal);

template<typename T>
void	printContainer(T &container)
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
		std::cout << container[i] << ' ';
	}
	std::cout << container[size -1] << std::endl;
};

#endif
