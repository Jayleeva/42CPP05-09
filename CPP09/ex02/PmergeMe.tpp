#include "PmergeMe.hpp"

template<typename T, typename Titerator>
void	standardBinaryInsert(T &container, unsigned int ui)
{
	size_t			i = 0;

	if (container.size() == 0)
	{
		container.push_back(ui);
		return ;
	}

	if (ui < container[0])
	{
		container.insert(container.begin(), ui);
		return ;
	}
	Titerator it = container.begin() + i;
	while (i + 1 < container.size())
	{
		if (ui > container[i] && ui < container[i + 1])
		{
			container.insert(it + 1, ui);
			return ;
		}
		it++;
		i++;
	}
	if (ui > container[container.size() -1] && ui < container[container.size()])
	{
		container.insert(it + 1, ui);
		return ;
	}
	if (ui > container[container.size()])
	{
		container.push_back(ui);
		return ;
	}
	std::cout << "not inserted" << std::endl;
};

template<typename T>
void	jacobsthalBinaryInsert(T *container, T *big, T *small)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_back(1);
	jacobsthal.push_back(3);

	if (size == 0)
	{
		container.push_back(big[i]);
		return ;
	}
	while (i < size)
	{
		std::cout << "i = " << i << std::endl;
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "standard" << std::endl;
			standardBinaryInsert(small, big[i]);
		}
		else
		{
			std::cout << "jacobsthal" << std::endl;
			standardBinaryInsert(small, big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	container.clear();
	container = small;
};

template<typename T>
void	splitBigSmall(T *current, T *big, T *small, char type)
{
	size_t	size = current.size();

	big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			standardBinaryInsert(small, current[i]);
			big.push_back(current[i + 1]);
		}
		else
		{
			standardBinaryInsert(small, current[i + 1]);
			big.push_back(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		standardBinaryInsert(small, current[i]);
		i++;
	}
	current.clear();
	current = big;
};

template<typename T>
void	mergePairs(size_t size, T *current, T *big, T *small, char type)
{
	if (size / 2 > 1)
		mergePairs(size / 2, current, big, small, type);
	splitBigSmall(current, big, small, type);
};

/*template<typename Tdata>
void		sortContainer(Tdata *data, char type)
{
	mergePairs(data->container.size(), data->container, data, type);
	jacobsthalBinaryInsert(data);
};*/

/*void		PmergeMe::sortContainer(t_dataVec *data, char type)
{
	mergePairs(data->container.size(), data->container, data, type);
	jacobsthalBinaryInsert(data);
};

void		PmergeMe::sortContainer(t_dataDeq *data, char type)
{
	mergePairs(data->container.size(), data->container, data, type);
	jacobsthalBinaryInsert(data);
};*/