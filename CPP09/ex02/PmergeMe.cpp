#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default constructor called" << DEFAULT << std::endl;
}

PmergeMe::PmergeMe(PmergeMe const &original)
{
	std::cout << YELLOW << "[PMERGEME] : Copy constructor called" << DEFAULT << std::endl;
	*this = original;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &original)
{
	if (this != &original)
	{
		this->dataVec.container = original.dataVec.container;
		this->dataDeq.container = original.dataDeq.container;
	}
	std::cout << YELLOW << "[PMERGEME] : Assignment operator overload called" << DEFAULT << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe()
{
	std::cout << YELLOW << "[PMERGEME] : Default destructor called" << DEFAULT << std::endl;
}

t_dataVec	PmergeMe::getDataVec() const
{
	return (this->dataVec);
}

t_dataDeq	PmergeMe::getDataDeq() const
{
	return (this->dataDeq);
}

void	PmergeMe::setDataVec(std::vector<unsigned int>::iterator begin, std::vector<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

void	PmergeMe::setDataDeq(std::deque<unsigned int>::iterator begin, std::deque<unsigned int>::iterator end)
{
	this->dataVec.container.insert(this->dataVec.container.end(), begin, end);
}

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}


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
	size_t				size = big->size();
	size_t				i = 0;
	size_t				remaining;
	unsigned int		ui;

	jacobsthal.push_back(1);
	jacobsthal.push_back(3);

	if (size == 0)
	{
		ui = big[i];
		container->push_back(ui);
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
			ui = big[i];
			standardBinaryInsert(small, ui);
		}
		else
		{
			std::cout << "jacobsthal" << std::endl;
			ui = big[jacobsthal[1]];
			standardBinaryInsert(small, ui);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	container->clear();
	container = small;
};

template<typename T>
void	splitBigSmall(T *current, T *big, T *small)
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
void	mergePairs(size_t size, T *current, T *big, T *small)
{
	if (size / 2 > 1)
		mergePairs(size / 2, current, big, small);
	splitBigSmall(current, big, small);
};



void		PmergeMe::sortVector(t_dataVec *data)
{
	mergePairs(data->container.size(), &(data->container), &(data->big), &(data->small));
	jacobsthalBinaryInsert(&(data->container), &(data->big), &(data->small));
}

void		PmergeMe::sortDequeue(t_dataDeq *data)
{
	mergePairs(data->container.size(), &(data->container), &(data->big), &(data->small));
	jacobsthalBinaryInsert(&(data->container), &(data->big), &(data->small));
}