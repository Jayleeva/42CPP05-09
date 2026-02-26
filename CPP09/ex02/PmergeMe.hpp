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
}								t_dataVec;

typedef struct s_dataDeq
{
	std::deque<unsigned int>	container;
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

		void	standardBinaryInsert(std::vector<unsigned int> &container, unsigned int ui);
		void	standardBinaryInsert(std::deque<unsigned int> &container, unsigned int ui);

		void	jacobsthalBinaryInsert(t_dataVec *data);
		void	jacobsthalBinaryInsert(t_dataDeq *data);

		void	splitBigSmall(std::vector<unsigned int> &current, t_dataVec *data);
		void	splitBigSmall(std::deque<unsigned int> &current, t_dataDeq *data);

		void	mergePairs(size_t size, std::vector<unsigned int> &current, t_dataVec *data);
		void	mergePairs(size_t size, std::deque<unsigned int> &current, t_dataDeq *data);

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal);


#endif
