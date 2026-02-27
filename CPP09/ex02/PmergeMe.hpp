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


typedef struct s_dataVec
{
	std::vector<unsigned int>	container;
	std::vector<unsigned int>	small;
	std::vector<unsigned int>	big;
	size_t						nlvl;
}								t_dataVec;

typedef struct s_dataDeq
{
	std::deque<std::pair<unsigned int, unsigned int> > pairs;
	std::deque<unsigned int>	container;
	std::deque<unsigned int>	main;
	std::deque<unsigned int>	pending;
	std::deque<unsigned int>	remaining;
	size_t						nlvl;
}								t_dataDeq;


class	PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &original);
		PmergeMe &operator=(PmergeMe const &original);
		~PmergeMe();

		t_dataVec	getDataVec() const;
		void		setDataVec(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end);
		t_dataDeq	getDataDeq() const;
		void		setDataDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end);

		/*template<typename T, typename Titerator>
		void	standardBinaryInsert(T &container, unsigned int ui);

		template<typename T>
		void	jacobsthalBinaryInsert(T *container, T *big, T *small);

		template<typename T>
		void	splitBigSmall(T *current, T *big, T *small);

		template<typename T>
		void	mergePairs(size_t size, T *current, T *big, T *small);*/

		void		sortVector(t_dataVec *data);
		void		sortDequeue(t_dataDeq *data);

	private:
		t_dataVec	dataVec;
		t_dataDeq	dataDeq;
};

		void	binaryInsert(std::vector<unsigned int> &container, unsigned int ui);
		void	binaryInsert(std::deque<unsigned int> &container, unsigned int ui);

		void	jacobsthalInsert(t_dataVec *data);
		void	jacobsthalInsert(t_dataDeq *data);

		void	swapSort(std::vector<unsigned int> &current, t_dataVec *data);
		void	swapSort(std::deque<unsigned int> &current, t_dataDeq *data);

		//void	mergeSort(size_t size, std::vector<unsigned int> &current, t_dataVec *data);
		//void	mergeSort(size_t size, std::deque<unsigned int> &current, t_dataDeq *data);
		void 	mergeSort2(std::deque<std::pair<unsigned int, unsigned int> >::iterator start, std::deque<std::pair<unsigned int, unsigned int> >::iterator end, size_t size);

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal);

template<typename T>
void	printContainer(T &container)
{
	size_t	max_ = 10;
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
