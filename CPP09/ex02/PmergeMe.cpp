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
	this->dataDeq.container.insert(this->dataDeq.container.end(), begin, end);
}

std::deque<size_t>	update_jacobsthal(std::deque<size_t> jacobsthal)
{
	size_t tmp1 = jacobsthal[0];
	size_t tmp2 = jacobsthal[1];
	jacobsthal[0] = tmp2;
	jacobsthal[1] = tmp1 * 2 + tmp2;
	return (jacobsthal);
}


void	standardBinaryInsert(std::vector<unsigned int> &container, unsigned int ui)
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
	std::vector<unsigned int>::iterator it = container.begin() + i;
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
	//std::cout << "not inserted" << std::endl;
};


void	standardBinaryInsert(std::deque<unsigned int> &container, unsigned int ui)
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
	std::deque<unsigned int>::iterator it = container.begin() + i;
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
	//std::cout << "not inserted" << std::endl;
};


void	jacobsthalBinaryInsert(t_dataVec *data)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = data->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);
	//std::cout << "[VEC] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	if (size == 0)
	{
		data->container.push_back(data->big[i]);
		return ;
	}
	while (i < size)
	{
		std::cout << "[VEC] i = " << i << std::endl;
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "[VEC] standard" << std::endl;
			standardBinaryInsert(data->small, data->big[i]);
		}
		else
		{
			std::cout << "[VEC] jacobsthal" << std::endl;
			standardBinaryInsert(data->small, data->big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	data->container.clear();
	data->container = data->small;
};

void	jacobsthalBinaryInsert(t_dataDeq *data)
{
	std::deque<size_t>	jacobsthal(2);
	size_t				size = data->big.size();
	size_t				i = 0;
	size_t				remaining;

	jacobsthal.push_front(3);
	jacobsthal.push_front(1);
	//std::cout << "[DEQ] jacob[0] = " << jacobsthal[0] << " jacob[1] = " << jacobsthal[1] << std::endl;

	//std::cout << "[DEQ] size during jac= " << data->big.size() << std::endl;
	//printContainer(data->big);

	if (size == 0)
	{
		data->container.push_back(data->big[i]);
		return ;
	}
	while (i < size)
	{
		std::cout << "[DEQ] i = " << i << std::endl;
		remaining = size - i;
		//std::cout << "jacob[1] = " << jacobsthal[1] << " jacob[0] = " << jacobsthal[0] << " remaining = " << remaining << std::endl;
		if (jacobsthal[1] - jacobsthal[0] > remaining)
		{
			std::cout << "[DEQ] standard" << std::endl;
			standardBinaryInsert(data->small, data->big[i]);
		}
		else
		{
			std::cout << "[DEQ] jacobsthal" << std::endl;
			standardBinaryInsert(data->small, data->big[jacobsthal[1]]);
		}
		jacobsthal = update_jacobsthal(jacobsthal);
		i ++;
	}
	data->container.clear();
	data->container = data->small;
};

void	splitBigSmall(std::vector<unsigned int> &current, t_dataVec *data)
{
	size_t	size = current.size();

	data->big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			standardBinaryInsert(data->small, current[i]);
			data->big.push_back(current[i + 1]);
		}
		else
		{
			standardBinaryInsert(data->small, current[i + 1]);
			data->big.push_back(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		standardBinaryInsert(data->small, current[i]);
		i++;
	}
	current.clear();
	current = data->big;
};

void	splitBigSmall(std::deque<unsigned int> &current, t_dataDeq *data)
{
	size_t	size = current.size();
	std::deque<unsigned int> newbig;

	//data->big.clear();
	size_t	i = 0;
	while (i + 1 < size)
	{
		if (current[i] < current[i + 1])
		{
			standardBinaryInsert(data->small, current[i]);
			newbig.push_back(current[i + 1]);
		}
		else
		{
			standardBinaryInsert(data->small, current[i + 1]);
			newbig.push_back(current[i]);
		}
		i += 2;
	}
	while (i < size)
	{
		standardBinaryInsert(data->small, current[i]);
		i++;
	}
	current.clear();
	current = newbig;
	data->big = newbig;

	//std::cout << "[DEQ] size before jac= " << data->big.size() << std::endl;
};

void	mergePairs(size_t size, std::vector<unsigned int> &current, t_dataVec *data)
{
	if (size / 2 > 1)
		mergePairs(size / 2, current, data);
	splitBigSmall(current, data);
}

void	mergePairs(size_t n, std::deque<unsigned int> &current, t_dataDeq *data)
{
	if (n > 1)
		mergePairs(--n, current, data);
	//if (size / 2 > 1)
	//	mergePairs(size / 2, current, data);
	splitBigSmall(current, data);
}


void		PmergeMe::sortVector(t_dataVec *data)
{
	mergePairs(data->container.size(), data->container, data);
	jacobsthalBinaryInsert(data);
}

void		PmergeMe::sortDequeue(t_dataDeq *data)
{
	size_t	size = data->container.size();
	size_t	n = 0;
	while (size / 2 > 1)
	{
		size /= 2;
		n ++;
	}
	std::cout << "n = " << n << std::endl;
	mergePairs(n, data->container, data);
	jacobsthalBinaryInsert(data);
}